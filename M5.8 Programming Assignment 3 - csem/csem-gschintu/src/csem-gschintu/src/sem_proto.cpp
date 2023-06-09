#include <stdio.h>

extern "C" {
    #include "cc.h"
    #include "scan.h"
    #include "semutil.h"
    #include "sem.h"
    #include "sym.h"
}

#include "llvm/Support/raw_ostream.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <utility>

/*
 * These have been extern'd from semutil.c. This handles local types of 
 * variables inside blocks, how many have been declared, and other things
 * I haven't quite figured out yet.
 */
extern int formalnum;               /* number of formal arguments */
extern char formaltypes[MAXARGS];   /* types of formal arguments  */
extern int localnum;                /* number of local variables  */
extern char localtypes[MAXLOCS];    /* types of local variables   */
extern int localwidths[MAXLOCS];    /* widths of local variables  */
extern struct id_entry* formalentries[MAXLOCS];   /* entries for parameters */
extern struct id_entry* localentries[MAXLOCS];   /* entries for local variables */

using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
/* The current function being parsed */
static Function* TheFunction;
/* The block inside the function where IR is being put */
static BasicBlock* TheBlock;
static std::map<std::string, AllocaInst*> local_values;
static std::map<std::string, std::pair<BasicBlock*, int>> local_labels;
static std::vector<std::pair<BasicBlock*, BasicBlock::iterator>> break_blocks;
static std::vector<std::pair<BasicBlock*, BasicBlock::iterator>> cont_blocks;
static std::vector<std::vector<std::pair<BasicBlock*, BasicBlock::iterator>>> loop_scopes;
static std::map<std::string, struct id_entry*> global_entries;
static int label_index = 0;

/* Short Circuit Branch Structure */
struct SCBranch {
    /* the block we're inserting the branch instructions into */
    BasicBlock *insert;
    /* Where we're inserting the instructions */
    BasicBlock::iterator pos;
    BasicBlock **trueB;
    BasicBlock **falseB;
    Value *cond;
    int is_negated;
    unsigned int scope;

    SCBranch (BasicBlock *insert, Value *cond, BasicBlock **t, BasicBlock **f, int scope)
        : insert(insert)
        , pos(std::prev(insert->end()))
        , trueB(t)
        , falseB(f)
        , cond(cond)
        , is_negated(false)
        , scope(scope)
    { }

    /*
     * Actually update a branch with a real label value.
     */
    void
    update_backpatch (bool branch, BasicBlock *label)
    {
        if (branch)
            *trueB = label;
        else
            *falseB = label;
    }

    void
    negate ()
    {
        is_negated = !is_negated;
    }

    Instruction *
    createBr ()
    {
        if (is_negated)
            return BranchInst::Create(*falseB, *trueB, cond);
        else
            return BranchInst::Create(*trueB, *falseB, cond);
    }
};

static unsigned int backpatch_scope = 0;
static std::list<SCBranch> backpatch_br;
static std::list<BasicBlock*> backpatch_loc;

/*
 * Update all locations that match the true/false location of L to the
 * true/false location of R. This is effectively merges multiples locations of
 * other SCBranch's to a single location so that location can be update later.
 */
void
merge_backpatch (bool branch, SCBranch *L, SCBranch *R)
{
    for (auto &Cond : backpatch_br) {
        if (branch && Cond.trueB == L->trueB)
            Cond.trueB = R->trueB;
        else if (!branch && Cond.falseB == L->falseB)
            Cond.falseB = R->falseB;
    }
}

/*
 * In the function for processing some logical conditions, the labels for where
 * to jump for the true and false branches will be known. This backpatches
 * those labels and finally inserts all the conditional branches now that all
 * information is present.
 */
void
insert_backpatch_conds (SCBranch *SC, BasicBlock *trueB, BasicBlock *falseB)
{
    SC->update_backpatch(true, trueB);
    SC->update_backpatch(false, falseB);
    for (auto &Cond : backpatch_br) {
        /* skip other scopes if present */
        if (Cond.scope != backpatch_scope)
            continue;
        Instruction *br = Cond.createBr();
        Cond.insert->getInstList().insertAfter(Cond.pos, br);
    }
    backpatch_scope--;
}

void
insert_loop_gotos (BasicBlock *contB, BasicBlock *exitB)
{
    Instruction *contBr = BranchInst::Create(contB);
    Instruction *breakBr = BranchInst::Create(exitB);

    for (auto &pair : break_blocks)
        pair.first->getInstList().insertAfter(pair.second, breakBr);
    for (auto &pair : cont_blocks)
        pair.first->getInstList().insertAfter(pair.second, contBr);
}

/*
 * Create a location that all SCBranch objects will hold.
 */
BasicBlock**
create_backpatch_loc (BasicBlock *label)
{
    backpatch_loc.push_back(label);
    return &backpatch_loc.back();
}

/*
 * Create an SCBranch object holding a NULL pointer for the labels for its
 * branch instruction.
 */
SCBranch *
create_backpatch_branch (BasicBlock *insert, struct sem_rec *R)
{
    BasicBlock **t = create_backpatch_loc(NULL);
    BasicBlock **f = create_backpatch_loc(NULL);
    SCBranch b(insert, (Value*) R->anything, t, f, backpatch_scope);
    backpatch_br.push_back(b);
    return &backpatch_br.back();
}

SCBranch *
get_backpatch_branch (struct sem_rec *R)
{
    return (SCBranch*) R->anything;
}

/*
 * Create a record of the latest backpatch locations. These records will
 * usually be used to update existing backpatch branches and then merged.
 */
struct sem_rec *
create_backpatch_record (SCBranch *B)
{
    struct sem_rec *R;
    R = node(0, T_LBL, NULL, NULL);
    R->anything = (void*) B;
    return R;
}

/*
 * Given a particular block, get the previous block.
 */
BasicBlock*
get_prev_block (BasicBlock *B)
{
    /*
     * Since we're being hacky just to produce a working program, this doesn't
     * use any sort of formal data structure. Labels are either "entry", some
     * user created label, or a label generated in the form L%d with m(). We
     * extract the digit and subtract by one. Blocks given to this function
     * should only be ones generated with the m() function.
     */
    const char *data = B->getName().data();
    std::string label = "L";
    auto it = local_labels.begin();
    int num;

    sscanf(data, "L%d\n", &num);

    if (num == 0) {
        return &TheFunction->getEntryBlock();
    }

    label += std::to_string(num - 1);
    it = local_labels.find(label);

    if (it == local_labels.end())
        goto error;

    return it->second.first;

error:
    fprintf(stderr, "cannot get prev of block `%s'\n", data);
    exit(1);
}

/*
 * Create a label entry into the local_labels table. If the label should be
 * defined then 'declared' should be 1. Otherwise, it should be 0. In all cases
 * a BasicBlock is created and stored under the label's name.
 */
BasicBlock*
create_label_entry (std::string id, int declared)
{
    if (local_labels.find(id) == local_labels.end()) {
        BasicBlock* B = BasicBlock::Create(TheContext, id, TheFunction);
        local_labels[id] = std::make_pair(B, declared);
    } else if (local_labels[id].second && declared) {
        yyerror("cannot declare label twice within scope");
    }

    local_labels[id].second = declared;
    return local_labels[id].first;
}

/*
 * Create an allocated instance of a variable inside the 'entry' of a function.
 */
AllocaInst*
create_func_alloca (Function *F, int type, int width, std::string var)
{
    Value *arr_size = NULL;
    IRBuilder<> B(&F->getEntryBlock(), F->getEntryBlock().begin());

    if (width > 1)
        arr_size = ConstantInt::get(Type::getInt32Ty(TheContext), width);

    switch (type) {
        case 'f':
            return B.CreateAlloca(Type::getDoubleTy(TheContext), arr_size, var);
        case 'i':
        default:
            return B.CreateAlloca(Type::getInt32Ty(TheContext), arr_size, var);
    }
}

/*
 * Given two semantic records, cast the right LLVM Value to match the left.
 */
Value*
cast_pair (struct sem_rec *left, struct sem_rec *right)
{
    Value *R = (Value*) right->anything;
    if ((left->s_mode & T_DOUBLE) && !(right->s_mode & T_DOUBLE))
        R = Builder.CreateSIToFP(R, Type::getDoubleTy(TheContext), "cast");
    else if ((left->s_mode & T_INT) && !(right->s_mode & T_INT))
        R = Builder.CreateFPToSI(R, Type::getInt32Ty(TheContext), "cast");
    return R;
}

/*
 * Globals must have an initialized value or else they are marked as being
 * external. This function specifies a global value of a specific width and
 * then initializes those bytes to 0, effectively making its linkage internal.
 */
void
global_alloc (struct id_entry *E, int width)
{
    std::string name(E->i_name);
    GlobalVariable *var;
    Type *type;
    Constant *init;

    if (E->i_type & T_INT) {
        if (E->i_type & T_ARRAY) {
            type = ArrayType::get(Type::getInt32Ty(TheContext), width);
            init = ConstantAggregateZero::get(type);
        }
        else {
            type = Type::getInt32Ty(TheContext);
            init = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
        }
    }
    else {
        init = ConstantInt::get(Type::getDoubleTy(TheContext), 0);
        if (E->i_type & T_ARRAY) {
            type = ArrayType::get(Type::getDoubleTy(TheContext), width);
            init = ConstantAggregateZero::get(type);
        }
        else {
            type = Type::getDoubleTy(TheContext);
            init = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
        }
    }

    TheModule->getOrInsertGlobal(name, type);
    var = TheModule->getNamedGlobal(name);
    var->setInitializer(init);

    E->anything = (void*) var;
}

/*
 * bgnstmt - encountered the beginning of a statement
 */
void
bgnstmt()
{
    /* todo ? */
}

/*
 * call - procedure invocation
 */
struct sem_rec *
call (const char *f, struct sem_rec *argsR)
{
    std::vector<Value*> args;
    struct sem_rec *R;
    struct id_entry *E;
    Type *rettype;
    Value *callInst;
    Function *F;

    /* have a reference to the first record */
    R = argsR;

    E = lookup(f, 0);
    if (!E) {
        std::string fname(f);
        if (global_entries.find(fname) == global_entries.end()) {
            fprintf(stderr, "cannot find function %s in namespace\n", f);
            exit(1);
        }
        E = global_entries[std::string(fname)];
    }

    /* get the necessary values for the CreateCall function */
    F = (Function*) E->anything;
    while (argsR != NULL) {
        args.push_back((Value*) argsR->anything);
        argsR = argsR->back.s_link;
    }

    callInst = Builder.CreateCall(F, makeArrayRef(args), "callret");

    rettype = TheFunction->getReturnType();

    /* use R to carry the return value of the function */
    if (rettype->isIntegerTy())
        R->s_mode = T_INT;
    else if (rettype->isDoubleTy())
        R->s_mode = T_DOUBLE;

    R->anything = (void*) callInst;

    return R;
}

struct sem_rec *
logical_backpatch (int type, struct sem_rec *e1, void *m, struct sem_rec *e2)
{
    SCBranch *L, *R;
    BasicBlock *prev;
    BasicBlock *curr;

    curr = (BasicBlock*) m;
    prev = get_prev_block(curr);

    if ((e1->s_mode & T_LBL) == 0) {
        L = create_backpatch_branch(prev, e1);
    } else {
        L = get_backpatch_branch(e1);
    }

    if ((e2->s_mode & T_LBL) == 0) {
        R = create_backpatch_branch(curr, e2);
    } else {
        R = get_backpatch_branch(e2);
    }

    if (type == 1) { /* AND */
        L->update_backpatch(true, curr);
        merge_backpatch(false, L, R);
    } else { /* OR */
        L->update_backpatch(false, curr);
        merge_backpatch(true, L, R);
    }

    return create_backpatch_record(R);
}

/*
 * ccand - logical and
 */
struct sem_rec *
ccand (struct sem_rec *e1, void* m, struct sem_rec *e2)
{
    return logical_backpatch(1, e1, m, e2);
}

/*
 * ccexpr - convert arithmetic expression to logical expression
 */
struct sem_rec *
ccexpr (struct sem_rec *R)
{
    Value *exp, *zero;

    exp = (Value*) R->anything;

    if (R->s_mode == T_INT) {
        zero = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
        R->anything = (void*) Builder.CreateICmpNE(exp, zero, "ccexpr");
    }
    else {
        zero = ConstantInt::get(Type::getDoubleTy(TheContext), 0);
        R->anything = (void*) Builder.CreateFCmpONE(exp, zero, "ccexpr");
    }

    return R;
}

/*
 * ccnot - logical not
 */
struct sem_rec *
ccnot (void *mS, struct sem_rec *E)
{
    BasicBlock *prev = (BasicBlock*) mS;
    SCBranch *N = create_backpatch_branch(prev, E);
    N->negate();
    return create_backpatch_record(N);
}

/*
 * ccor - logical or
 */
struct sem_rec *
ccor (struct sem_rec *e1, void* m, struct sem_rec *e2)
{
    return logical_backpatch(0, e1, m, e2);
}

/*
 * con - constant reference in an expression
 */
struct sem_rec*
con (const char *x)
{
    struct sem_rec *R;
    struct id_entry *E;
    int v;

    E = lookup(x, 0);
    if (!E)
        E = install(x, 0);
    /*
     * Use 'anything' part of record to hold our value. This is used int
     * doret to make a retval of the constant here.
     */
    R = node(currtemp(), T_INT, NULL, NULL);
    sscanf(x, "%d", &v);
    R->anything = (void*) ConstantInt::get(Type::getInt32Ty(TheContext), v);
    R->s_mode |= T_INT;
    R->id = E;
    return R;
}

/*
 * dobreak - break statement
 */
void
dobreak ()
{
    /*
     * We add the current block and an iterator the current block's last
     * instruction. This lets us insert the branch to the end of the loop after
     * that instruction later.
     */
    break_blocks.push_back(std::make_pair(TheBlock, std::prev(TheBlock->end())));
}

/*
 * docontinue - continue statement
 */
void docontinue()
{
    cont_blocks.push_back(std::make_pair(TheBlock, std::prev(TheBlock->end())));
}

/*
 * dodo - do statement
 */
void
dodo (void *mS, void* m1, void* m2, struct sem_rec *R, void* m3)
{
    Value *cond;
    BasicBlock *startB, *loopB, *codeB, *exitB;

    cond = (Value*) R->anything;
    startB = (BasicBlock*) mS;
    codeB  = (BasicBlock*) m1;
    loopB = (BasicBlock*) m2;
    exitB = (BasicBlock*) m3;

    /* the loop has the conditional jump */
    if (R->s_mode & T_LBL) {
        insert_backpatch_conds(get_backpatch_branch(R), codeB, exitB);
    } else {
        Builder.SetInsertPoint(loopB);
        Builder.CreateCondBr(cond, codeB, exitB);
    }

    /* Since it's a do-statement, the start jumps straight into the code */
    Builder.SetInsertPoint(startB);
    Builder.CreateBr(codeB);

    codeB = get_prev_block(exitB);
    Builder.SetInsertPoint(codeB);
    Builder.CreateBr(loopB);

    insert_loop_gotos(loopB, exitB);

    endloopscope(0);
    Builder.SetInsertPoint(TheBlock);
}

/*
 * dofor - for statement
 */
void
dofor (void* mS, void* m1, struct sem_rec *R1, void* m2, struct sem_rec *R2,
           void* m3, struct sem_rec *R3, void* m4)
{
    Value *cond;
    BasicBlock *startB, *condB, *incB, *codeB, *exitB;

    cond = (Value*) R1->anything;
    startB = (BasicBlock*) mS;
    condB = (BasicBlock*) m1;
    incB = (BasicBlock*) m2;
    codeB  = (BasicBlock*) m3;
    exitB = (BasicBlock*) m4;

    Builder.SetInsertPoint(startB);
    Builder.CreateBr(condB);

    if (R1->s_mode & T_LBL) {
        insert_backpatch_conds(get_backpatch_branch(R1), codeB, exitB);
    } else {
        Builder.SetInsertPoint(condB);
        Builder.CreateCondBr(cond, codeB, exitB);
    }

    /* for's jump to the 'increment' which then jumps to the conditional */
    codeB = get_prev_block(exitB);
    Builder.SetInsertPoint(codeB);
    Builder.CreateBr(incB);

    Builder.SetInsertPoint(incB);
    Builder.CreateBr(condB);

    insert_loop_gotos(incB, exitB);

    endloopscope(0);
    Builder.SetInsertPoint(TheBlock);
}

/*
 * dogoto - goto statement
 */
void
dogoto (const char *id)
{
    /* Create a label entry but do not define it yet */
    BasicBlock *B = create_label_entry(std::string(id), 0);
    /* Create a branch to the block even if that block has not been defined */
    Builder.CreateBr(B);
}

/*
 * doif - one-arm if statement
 */
void
doif (void* mS, struct sem_rec *R, void* m1, void* m2)
{
    Value *cond;
    BasicBlock *startB, *thenB, *mergeB;

    cond = (Value*) R->anything;
    startB = (BasicBlock*) mS;
    thenB = (BasicBlock*) m1;
    mergeB = (BasicBlock*) m2;

    /* If the semantic record is a backpatch label */
    if (R->s_mode & T_LBL) {
        insert_backpatch_conds(get_backpatch_branch(R), thenB, mergeB);
    } else {
        Builder.SetInsertPoint(startB);
        Builder.CreateCondBr(cond, thenB, mergeB);
    }

    thenB = get_prev_block(mergeB);
    Builder.SetInsertPoint(thenB);
    Builder.CreateBr(mergeB);

    Builder.SetInsertPoint(TheBlock);
}

/*
 * doifelse - if then else statement
 */
void
doifelse (void* mS, struct sem_rec *R1, void* m1, struct sem_rec *R2,
                         void* m2, void* m3)
{
    Value *cond;
    BasicBlock *startB, *thenB, *elseB, *mergeB;

    cond = (Value*) R1->anything;
    startB = (BasicBlock*) mS;
    thenB = (BasicBlock*) m1;
    elseB  = (BasicBlock*) m2;
    mergeB = (BasicBlock*) m3;

    /* If the semantic record is a backpatch label */
    if (R1->s_mode & T_LBL) {
        insert_backpatch_conds(get_backpatch_branch(R1), thenB, elseB);
    } else {
        Builder.SetInsertPoint(startB);
        Builder.CreateCondBr(cond, thenB, elseB);
    }

    thenB = get_prev_block(elseB);
    Builder.SetInsertPoint(thenB);
    Builder.CreateBr(mergeB);

    elseB = get_prev_block(mergeB);
    Builder.SetInsertPoint(elseB);
    Builder.CreateBr(mergeB);

    Builder.SetInsertPoint(TheBlock);
}

/*
 * doret - return statement
 */
void
doret (struct sem_rec *R)
{
    if (!R) {
        Builder.CreateRetVoid();
        return;
    }

    Type *rettype, *valtype;
    Value *value;

    /* Make sure the value matches the return type of the function */
    value = (Value*) R->anything;
    valtype = value->getType();
    rettype = TheFunction->getReturnType();

    if (rettype->isIntegerTy() && valtype != rettype)
        value = Builder.CreateFPToSI(value, TheFunction->getReturnType(), "cast");
    else if (rettype->isDoubleTy() && valtype != rettype)
        value = Builder.CreateSIToFP(value, TheFunction->getReturnType(), "cast");

    Builder.CreateRet(value);
}

/*
 * dowhile - while statement
 */
void
dowhile (void* mS, void* m1,
            struct sem_rec *R, void* m2, struct sem_rec *n, void* m3)
{
    Value *cond;
    BasicBlock *startB, *loopB, *codeB, *exitB;

    cond = (Value*) R->anything;
    startB = (BasicBlock*) mS;
    loopB = (BasicBlock*) m1;
    codeB  = (BasicBlock*) m2;
    exitB = (BasicBlock*) m3;

    /* the loop has the conditional jump */
    if (R->s_mode & T_LBL) {
        insert_backpatch_conds(get_backpatch_branch(R), codeB, exitB);
    } else {
        Builder.SetInsertPoint(loopB);
        Builder.CreateCondBr(cond, codeB, exitB);
    }

    /* the main block before the while jumps to the loop */
    Builder.SetInsertPoint(startB);
    Builder.CreateBr(loopB);

    /*
     * Since there can be expressions within a while loop, we find where the
     * loop exits, then go one block back and use that to jump back to the
     * beginning of the loop.
     */
    codeB = get_prev_block(exitB);
    Builder.SetInsertPoint(codeB);
    Builder.CreateBr(loopB);

    /*
     * For each blocks that has a break, we insert a branch to the exit of the
     * loop just after the last instruction recorded when that block had a
     * break statement.
     */
    insert_loop_gotos(loopB, exitB);

    endloopscope(0);
    Builder.SetInsertPoint(TheBlock);
}

/*
 * endloopscope - end the scope for a loop
 */
void
endloopscope (int m)
{
    cont_blocks = loop_scopes.back();
    loop_scopes.pop_back();
    break_blocks = loop_scopes.back();
    loop_scopes.pop_back();
}

/*
 * exprs - form a list of expressions
 */
struct sem_rec *
exprs (struct sem_rec *L, struct sem_rec *R)
{
    struct sem_rec *LIST;
    /* naively walk the list until the end is found and append */
    LIST = L;
    while (L->back.s_link)
        L = L->back.s_link;
    L->back.s_link = R;
    R->back.s_link = NULL;
    return LIST;
}

/*
 * Take a constructed function id_entry and add it to the LLVM AST.
 */
void
fhead (struct id_entry *E)
{
    std::vector<Type*> args;
    Type* func_type;
    GlobalValue::LinkageTypes linkage;
	FunctionType *FT;
    Function *F;
    BasicBlock *B;
    int i;

    /* push back each function argument */
    for (i = 0; i < formalnum; i++) {
        switch (formaltypes[i]) {
            case 'f': args.push_back(Type::getDoubleTy(TheContext)); break;
            case 'i': args.push_back(Type::getInt32Ty(TheContext)); break;
            default:  yyerror("type failure!");
        }
    }

    /* handle function return type */
    switch (E->i_type) {
        case T_INT:    func_type = Type::getInt32Ty(TheContext); break;
        case T_DOUBLE: func_type = Type::getDoubleTy(TheContext); break;
    }
	FT = FunctionType::get(func_type, makeArrayRef(args), false);

    /* need main to be entry point into program for linking */
    if (strcmp(E->i_name, "main") == 0) {
        linkage = Function::ExternalLinkage;
    } else {
        linkage = Function::InternalLinkage;
    }
	
    F = Function::Create(FT, linkage, E->i_name, TheModule.get());
    E->anything = (void*) F;

    /* name each function argument */
    i = 0;
    for (auto &arg : F->args())
        arg.setName(formalentries[i++]->i_name);

    B = BasicBlock::Create(TheContext, "entry", F);
    Builder.SetInsertPoint(B);

    /* The following resets all data structures for the function scope. */
    backpatch_br.clear();
    backpatch_loc.clear();
    local_values.clear();
    local_labels.clear();
    label_index = 0;

    /* 
     * We have binded the arguments to create function F. Now we must allocate
     * instances of them so they can be referenced and also mutated.
     */
    i = 0;
	for (auto &arg : F->args()) {
        std::string name = arg.getName();
        auto value = create_func_alloca(F, formaltypes[i++], 1, name);
        /* assign the initial value of the parameter (from a function call) */
        Builder.CreateStore(&arg, value);
        local_values[name] = value;
	}

    /* Create the instance of stack memory for each local variable */
    for (i = 0; i < localnum; i++) {
        std::string name = std::string(localentries[i]->i_name);
        auto value = create_func_alloca(F, localtypes[i], localwidths[i], name);
        local_values[name] = value;
    }

    TheFunction = F;
    TheBlock = B;
}

/*
 * Create and fill up an id_entry with the correct information.
 */
struct id_entry*
fname (int type, const char *id)
{
    struct id_entry *E = lookup(id, 0);

    /* add function to hash table if it doesn't exist */
    if (!E)
        E = install(id, 0);

    /* cannot have two functions of the same name */
    if (E->i_defined)
        yyerror("cannot declare function more than once");

    E->i_type = type;
	E->i_scope = GLOBAL;
	E->i_defined = true;

    /* need to enter the block to let hash table do internal work */
    enterblock();
    /* then need to reset argument count variables */
    formalnum = 0;
    localnum = 0;

    return E;
}

/*
 * ftail - end of function body
 */
void
ftail()
{
    /* 
     * Handle implicit fall-throughs of blocks. If a block has no instructions
     * in it, then simply create a branch to the next block. If a block has
     * instructions but not a terminating instruction (branch or ret) then 
     * create branch to the next instruction.
     */
    Function *F = TheFunction;
    for (auto it = F->begin(); it != F->end(); it++) {
        if (it->size() == 0 || !it->back().isTerminator()) {
            if (std::next(it) != F->end()) {
                Builder.SetInsertPoint(&(*it));
                Builder.CreateBr(&(*std::next(it)));
            } else {
                yyerror("cannot having implicit fallthrough on last block!");
            }
        }
    }
    Builder.SetInsertPoint(TheBlock);
    leaveblock();
}

/*
 * id - variable reference
 */
struct sem_rec *
id (const char *x)
{
    struct sem_rec *R;
    struct id_entry *E;
    std::string name(x);

    E = lookup(x, 0);
    if (!E) {
        yyerror("undefined reference");
    }

    R = node(currtemp(), E->i_type, NULL, NULL);
    R->id = E;

    if (E->i_scope == GLOBAL) {
        R->anything = E->anything;
    }
    else {
        R->anything = (void*) local_values[std::string(x)];
    }

    return R;
}

/*
 * indx - subscript
 */
struct sem_rec *
indx (struct sem_rec *x, struct sem_rec *i)
{
    Value *arr, *idx;
    struct sem_rec *R;

    arr = (Value*) x->anything;
    idx = (Value*) i->anything;

    R = node(currtemp(), x->s_mode, NULL, NULL);
    R->anything = (void*) Builder.CreateGEP(arr, idx, "indx");
    /*
     * Global arrays are specified differently and must have their GEP'd
     * pointer casted to a regular integer pointer before storing.
     */
    if (x->id->i_scope == GLOBAL && x->id->i_type & T_ARRAY) {
        Type *type;
        if (x->id->i_type & T_INT)
            type = PointerType::get(Type::getInt32Ty(TheContext), 0);
        else
            type = PointerType::get(Type::getDoubleTy(TheContext), 0);
        R->anything = (void*) Builder.CreateBitCast((Value*) R->anything, type, "ptrcast");
    }
    R->id = x->id;
    return R;
}

/*
 * labeldcl - process a label declaration
 */
void
labeldcl (const char *id)
{
    /* 
     * Create a label if it first doesn't exist. Then set the IR's insert point
     * to that label's block.
     */
    BasicBlock *B = create_label_entry(std::string(id), 1);
    /* need to make sure end of block has an return or branch statement */
    Builder.CreateBr(B);
    Builder.SetInsertPoint(B);
}

/*
 * Return the current block. If a new backpatching scope should be created at
 * the current block, then increment the scope number.
 */
void*
m_get (int new_backpatch_scope)
{
    if (new_backpatch_scope)
        backpatch_scope++;
    return TheBlock;
}

/*
 * m - generate label and return next temporary number
 */
void*
m ()
{
    /* Generate unique label names using a static counter */
    std::string label = "L" + std::to_string(label_index++);
    BasicBlock *B = create_label_entry(label, 1);
    TheBlock = B;
    Builder.SetInsertPoint(B);
    return B;
}

/*
 * n - generate goto and return backpatch pointer
 */
struct sem_rec *n()
{
    return NULL;
}

/*
 * op1 - unary operators
 */
struct sem_rec *
op1 (const char *op, struct sem_rec *y)
{
    std::string var(y->id->i_name);
    Value *variable = (Value*) y->anything;

    switch (*op) {
        case '@':
            /*
             * Very confusing. 'variable' first takes the value of the instance
             * of the variable inside the semantic record 'y' which is basically
             * a pointer. Then we create a 'load' or dereference of that
             * variable and overwrite the semantic record with that value.
             */
            y->anything = (void*) Builder.CreateLoad(variable, var);
            break;
        case '~':
            y->anything = (void*) Builder.CreateNot(variable, var);
            break;
        case '-':
            if (y->s_mode & T_INT)
                y->anything = (void*) Builder.CreateNeg(variable, var);
            else
                y->anything = (void*) Builder.CreateFNeg(variable, var);
            break;
        default:
            fprintf(stderr, "sem: op1 %s not implemented\n", op);
            return NULL;
    }

    return y;
}

Value*
llvm_op2 (const char *op, int type, Value *L, Value *R)
{
    switch (*op) {
        case '+':
            if (type == T_INT)
                return Builder.CreateAdd(L, R, "addtmp");
            else
                return Builder.CreateFAdd(L, R, "addtmp");
            break;
        case '-':
            if (type == T_INT)
                return Builder.CreateSub(L, R, "subtmp");
            else
                return Builder.CreateFSub(L, R, "subtmp");
            break;
        case '*':
            if (type == T_INT)
                return Builder.CreateMul(L, R, "multmp");
            else
                return Builder.CreateFMul(L, R, "multmp");
            break;
        case '/':
            if (type == T_INT)
                return Builder.CreateSDiv(L, R, "divtmp");
            else
                return Builder.CreateFDiv(L, R, "divtmp");
            break;
        case '%':
            if (type == T_INT)
                return Builder.CreateSRem(L, R, "remtmp");
            else
                return Builder.CreateFRem(L, R, "remtmp");
            break;
        default:
           fprintf(stderr, "sem: op2 %s not implemented\n", op);
           return NULL;
    }
}

/*
 * op2 - arithmetic operators
 */
struct sem_rec *
op2 (const char *op, struct sem_rec *x, struct sem_rec *y)
{
    Value *L, *R;

    L = (Value*) x->anything;
    R = cast_pair(x, y);

    x->anything = (void*) llvm_op2(op, x->id->i_type, L, R);
    return x;
}

/*
 * opb - bitwise operators
 */
struct sem_rec *opb(const char *op, struct sem_rec *x, struct sem_rec *y)
{
   fprintf(stderr, "sem: opb not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * rel - relational operators
 */
struct sem_rec *
rel (const char *op, struct sem_rec *x, struct sem_rec *y)
{
    Value *L, *R;

    L = (Value*) x->anything;
    R = cast_pair(x, y);

    switch (*op) {
        case '=':
            if (x->s_mode == T_INT)
                x->anything = (void*) Builder.CreateICmpEQ(L, R, "eqtmp");
            else
                x->anything = (void*) Builder.CreateFCmpOEQ(L, R, "eqtmp");
            break;

        case '!':
            if (x->s_mode == T_INT)
                x->anything = (void*) Builder.CreateICmpNE(L, R, "netmp");
            else
                x->anything = (void*) Builder.CreateFCmpONE(L, R, "netmp");
            break;

        case '>':
            if (op[1] == '\0') {
                if (x->s_mode == T_INT)
                    x->anything = (void*) Builder.CreateICmpSGT(L, R, "sgttmp");
                else
                    x->anything = (void*) Builder.CreateFCmpOGT(L, R, "sgttmp");
            }
            else {
                if (x->s_mode == T_INT)
                    x->anything = (void*) Builder.CreateICmpSGE(L, R, "sgetmp");
                else
                    x->anything = (void*) Builder.CreateFCmpOGE(L, R, "sgetmp");
            }
            break;
        case '<':
            if (op[1] == '\0') {
                if (x->s_mode == T_INT)
                    x->anything = (void*) Builder.CreateICmpSLT(L, R, "slttmp");
                else
                    x->anything = (void*) Builder.CreateFCmpOLT(L, R, "slttmp");
            }
            else {
                if (x->s_mode == T_INT)
                    x->anything = (void*) Builder.CreateICmpSLE(L, R, "sletmp");
                else
                    x->anything = (void*) Builder.CreateFCmpOLE(L, R, "sletmp");
            }
            break;
        default:
            fprintf(stderr, "sem: rel %s not implemented\n", op);
            return NULL;
    }

    return x;
}

/*
 * set - assignment operators
 */
struct sem_rec *
set (const char *op, struct sem_rec *x, struct sem_rec *y)
{
    Value *storage, *tmp, *value;

    storage = (Value*) x->anything;
    value = cast_pair(x, y);

    /*
     * Use the op2 function to handle any op-assignment operations. The storage
     * value itself is used as the left-hand operand. This means we must first
     * dereference the lval to use it for some op. Then the return of that op
     * is stored at the lval.
     */
    if (*op != '\0') {
        tmp = Builder.CreateLoad(storage, std::string(x->id->i_name));
        value = llvm_op2(op, x->id->i_type, tmp, value);
    }

    Builder.CreateStore(value, storage);
    x->anything = (void*) value;
    return x;
}

/*
 * startloopscope - start the scope for a loop
 */
void
startloopscope ()
{
    loop_scopes.push_back(break_blocks);
    loop_scopes.push_back(cont_blocks);
    break_blocks.clear();
    cont_blocks.clear();
}

/*
 * string - generate code for a string
 */
struct sem_rec *
string (const char *s)
{
    struct sem_rec *R;
    R = node(currtemp(), T_STR, NULL, NULL);
    R->anything = (void*) Builder.CreateGlobalStringPtr(s, s);
    return R;
}

void
init_IR ()
{
    struct id_entry *E;
	FunctionType *var_arg;
    Constant *F;
    std::string fname = "printf";

    TheModule = llvm::make_unique<Module>("LEROY", TheContext);

    /* Add printf to our internal data structure */
	var_arg = FunctionType::get(IntegerType::getInt32Ty(TheContext),
                PointerType::get(Type::getInt32Ty(TheContext), 0), true);
    F = TheModule->getOrInsertFunction("printf",
            FunctionType::get(IntegerType::getInt32Ty(TheContext), var_arg));

    E = (struct id_entry*) malloc(sizeof(struct id_entry));
    E->i_type = 0;
    E->i_scope = GLOBAL;
    E->i_defined = true;
    E->anything = (void*) F;

    global_entries[fname] = E;
}

void
emit_IR ()
{
    TheModule->print(outs(), nullptr);

    for (auto &E : global_entries)
        free(E.second);
}