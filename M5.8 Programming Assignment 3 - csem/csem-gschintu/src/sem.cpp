#include <stdio.h>

extern "C" {
    #include "cc.h"
    #include "scan.h"
    #include "semutil.h"
    #include "sem.h"
    #include "sym.h"
}

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/Function.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include <utility>
#include <cstdlib>
#include <memory>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
#include <map>

# define MAXLOOPNEST 50
# define MAXLABELS 50
# define MAXGOTOS 50

using std::map;
using std::string;
using std::vector;
using llvm::outs;
using llvm::Type;
using llvm::Value;
using llvm::Module;
using llvm::Function;
using llvm::Constant;
using llvm::IRBuilder;
using llvm::ArrayType;
using llvm::BasicBlock;
using llvm::AllocaInst;
using llvm::BranchInst;
using llvm::Instruction;
using llvm::LLVMContext;
using llvm::ConstantInt;
using llvm::GlobalValue;
using llvm::IntegerType;
using llvm::PointerType;
using llvm::FunctionType;
using llvm::GlobalVariable;
using llvm::ConstantAggregateZero;

extern int formalnum;                         /* number of formal arguments */
extern struct id_entry* formalvars[MAXLOCS];  /* entries for parameters */
extern int localnum;                          /* number of local variables  */
extern struct id_entry* localvars[MAXLOCS];   /* entries for local variables */

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

static int label_index = 0;
int relexpr = 0;

struct loopscope {
  struct sem_rec* breaks;
  struct sem_rec* conts;
} lscopes[MAXLOOPNEST];

static int looplevel = 0;
struct loopscope *looptop = (struct loopscope *) NULL;

struct labelnode {
   const char *id;    /* label string    */
   BasicBlock *bb;    /* basic block for label */
} labels[MAXLABELS];

struct gotonode {
   const char *id;     /* label string in goto statement */
   BranchInst *branch; /* branch to temporary label */
} gotos[MAXGOTOS];     /* list of gotos to be backpatched */

int numgotos = 0;    /* number of gotos to be backpatched */
int numlabelids = 0; /* total label ids in function */

std::string new_label()
{
  return ("L" + std::to_string(label_index++));
}

BasicBlock*
create_tmp_label()
{
  return BasicBlock::Create(TheContext);
}

BasicBlock*
create_named_label(std::string label)
{
  Function *curr_func = Builder.GetInsertBlock()->getParent();
  BasicBlock *new_block = BasicBlock::Create(TheContext, label, curr_func);
  return new_block;
}

/*
 * Given two semantic records, cast the right LLVM Value to match the left.
 */
Value*
cast_Rval (struct sem_rec *left, struct sem_rec *right)
{
  Value *R = (Value*) right->s_value;
  if ((left->s_type == T_DOUBLE) )
      R = Builder.CreateSIToFP((Value*)right->s_value, Type::getDoubleTy(TheContext));
  else if ((left->s_type == T_INT) )
      R = Builder.CreateFPToSI((Value*)right->s_value, Type::getInt32Ty(TheContext));
/*      
  else if (left->s_type == right->s_type)
      R = (Value*) right->s_value;
*/
  else{
    fprintf(stderr, "cast_Rval: cast not implemented\n");
    fprintf(stderr, "left->s_type=%d and right->s_type=%d  R=%s\n", left->s_type,right->s_type, R); 

  }

  return R;
}

/*
 * Given two semantic records, cast the right LLVM Value to match the left.
 */
Value*
cast_Rval (struct sem_rec *e, int t)
{
  Value *R = (Value*) e->s_value;
  if ((e->s_type & T_INT) && (t & T_DOUBLE) ){
  fprintf(stderr, "cast_Rval: intoTodouble\n");
      R = Builder.CreateSIToFP((Value*)e->s_value, Type::getDoubleTy(TheContext));
  }else if ((e->s_type & T_DOUBLE) && (t & T_INT) ){
    fprintf(stderr, "cast_Rval: doubleToint\n");
      R = Builder.CreateFPToSI((Value*)e->s_value, Type::getInt32Ty(TheContext));
  }else{
    fprintf(stderr, "cast_Rval: cast not implemented\n");
    fprintf(stderr, "e->s_type=%d | R=%s\n", e->s_type, R); 

  }
  return R;
}



/*
 * cast - cast value to a different type
 *
 * LLVM API calls:
 * IRBuilder::CreateSIToFP(Value *, Type *)
 * IRBuilder::CreateFPToSI(Value *, Type *)
 * Type::getInt32Ty(LLVMContext &)
 * Type::getDoubleTy(LLVMContext &)
 */
struct sem_rec*
cast (struct sem_rec *y, int t)
{
  Value *R = (Value*) y->s_value;
  struct sem_rec *rec = nullptr;
  if ((t & T_DOUBLE) && !(y->s_type & T_DOUBLE)){
    rec =  s_node ( (void *)Builder.CreateSIToFP(R, Type::getDoubleTy(TheContext)), T_DOUBLE);
  } else if ((t & T_INT) && !(y->s_type & T_INT)){
    rec =  s_node ( (void *)Builder.CreateFPToSI(R, Type::getInt32Ty(TheContext)), T_INT);
  }

  return rec;

  //fprintf(stderr, "sem: cast not implemented\n");
  //return ((struct sem_rec *) NULL);
}

/*
 * startloopscope - start the scope for a loop
 */
void
startloopscope()
{
   looptop = &lscopes[looplevel++];
   if (looptop > lscopes+MAXLOOPNEST) {
      fprintf(stderr, "loop nest too great\n");
      exit(1);
   }
   looptop->breaks = (struct sem_rec *) NULL;
   looptop->conts = (struct sem_rec *) NULL;
}

/*
 * endloopscope - end the scope for a loop
 */
void
endloopscope()
{
  looplevel--;
  looptop--;
}


/*
 * Global allocations. Globals are initialized to 0.
 */
void
global_alloc (struct id_entry *p, int width)
{
  string name(p->i_name);
  GlobalVariable *var;
  Type *type;
  Constant *init;

  if (p->i_type & T_INT) {
    if (p->i_type & T_ARRAY) {
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
    if (p->i_type & T_ARRAY) {
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
  p->i_value = (void*) var; 
}


/*
 * backpatch - set temporary labels in the sem_rec to real labels
 *
 * LLVM API calls:
 *
 * llvm::dyn_cast<BranchInst>(Value*)
 * BranchInst::getNumSuccessors()
 * BranchInst::getSuccessor(unsigned)
 * BranchInst::setSuccessor(unsigned, BasicBlock*)
 */

void backpatch(struct sem_rec *rec, void *bb)
{
  unsigned i;
  BranchInst *br_inst;

  while (rec != NULL) {
    if ((br_inst = llvm::dyn_cast<BranchInst>((Value*) rec->s_value))) {
      for (i = 0; i < br_inst->getNumSuccessors(); i++) {
        if (br_inst->getSuccessor(i) == ((BasicBlock*) rec->s_bb)) {
          br_inst->setSuccessor(i, (BasicBlock *) bb);
        }
      }
    } else {
      fprintf(stderr, "error: backpatch with non-branch \n");
      //exit(1);
    }
    rec = rec->s_link;
  }
}

/*
 * call - procedure invocation
 *
 * Grammar:
 * lval -> ID '(' ')'            { $$ = call($1, (struct sem_rec *) NULL); }
 * lval -> ID '(' exprs ')'      { $$ = call($1, $3); }
 *
 * LLVM API calls:
 * makeArrayRef(vector<Value*>)
 * IRBuilder::CreateCall(Function *, ArrayRef<Value*>)
 */
struct sem_rec*
call(char *f, struct sem_rec *argsR)
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

  /* get the necessary values for the CreateCall function */
  F = (Function*) E->i_value;
  while (argsR != NULL) {
      args.push_back((Value*) argsR->s_value);
      argsR = argsR->s_link;
  }

  callInst = Builder.CreateCall(F, makeArrayRef(args), "callret");

  R->s_type = E->i_type; // not sure about this one
  R->s_value = (void*) callInst;
  
  return R;

 // fprintf(stderr, "sem: call not implemented\n");
 // return ((struct sem_rec*) NULL);
}


/*
 * ccand - logical and
 *
 * Grammar:
 * cexpr -> cexpr AND m cexpr     { $$ = ccand($1, $3, $4); }
 *
 * LLVM API calls:
 * None
 */
struct sem_rec*
ccand(struct sem_rec *e1, void *m, struct sem_rec *e2)
{
  backpatch(e1->s_true, m);

  return node((void *) NULL,(void *) NULL, 0,(struct sem_rec*) NULL,e2->s_true, merge(e1->s_false, e2->s_false));

  //fprintf(stderr, "sem: ccand not implemented\n" );
  //return ((struct sem_rec*) NULL);
}

/*
 * ccexpr - convert arithmetic expression to logical expression
 *
 * Grammar:
 * cexpr -> expr                  { $$ = ccexpr($1); }
 *
 * LLVM API calls:
 *
 * IRBuilder::CreateICmpNE(Value *, Value *)
 * IRBuilder::CreateFCmpONE(Value *, Value *)
 * IRBuilder::CreateCondBr(Value *, BasicBlock *, BasicBlock *)
 */
struct sem_rec *
ccexpr(struct sem_rec *e)
{
  BasicBlock *tmp_true, *tmp_false;
  Value *val, *cmp;
  tmp_true = create_tmp_label();
  tmp_false = create_tmp_label();
  cmp = (Value *)e->s_value;

  fprintf(stderr, "ccexpr | e->s_value=%d\n", e->s_value);

  val = Builder.CreateCondBr(cmp, tmp_true, tmp_false);

  return ( node((void *) NULL,(void *) NULL, 0, (struct sem_rec*) NULL,
                (node ( val, tmp_true, 0, (struct sem_rec*) NULL,
                        (struct sem_rec*) NULL, (struct sem_rec*) NULL)),
                (node ( val, tmp_false, 0, (struct sem_rec*) NULL,
                        (struct sem_rec*) NULL, (struct sem_rec*) NULL ))
                )
          );
}

/*
 * ccnot - logical not
 *
 * Grammar:
 * cexpr -> NOT cexpr             { $$ = ccnot($2); }
 *
 * LLVM API calls:
 * None
 */
struct sem_rec*
ccnot(struct sem_rec *e)
{
  
  return node((void *) NULL,(void *) NULL, 0,(struct sem_rec*) NULL,e->s_false, e->s_true);

  //fprintf(stderr, "sem: ccnot not implemented\n");
  //return ((struct sem_rec *) NULL);
}

/*
 * ccor - logical or
 *
 * Grammar:
 * cexpr -> cexpr OR m cexpr      { $$ = ccor($1, $3, $4); }
 *
 * LLVM API calls:
 * None -- but uses backpatch
 */
struct sem_rec*
ccor(struct sem_rec *e1, void *m, struct sem_rec *e2)
{

  backpatch(e1->s_false, m);

  return node((void *) NULL,(void *) NULL, 0,(struct sem_rec*) NULL, merge(e1->s_true, e2->s_true), e2->s_false); 


  //fprintf(stderr, "sem: ccor not implemented\n");
  //return NULL;
}

/*
 * con - constant reference in an expression
 *
 * Grammar:
 * expr -> CON                   { $$ = con($1); }
 *
 * LLVM API calls:
 * Type::getInt32Ty(LLVMContext&);
 * ConstantInt::get(Type*, uint64_t, bool)
 */
struct sem_rec*
con(const char *x)
{
  struct id_entry *entry;
  if ((entry = lookup(x, 0)) == NULL) {
    entry = install (x, 0);
    entry->i_type = T_INT;
    entry->i_scope = GLOBAL;
    entry->i_defined = 1;
  }

  entry->i_value = (void *) ConstantInt::get(Type::getInt32Ty(TheContext), std::stoi(x));
  return (s_node ((void*) entry->i_value, entry->i_type));

  //fprintf(stderr, "sem: remainder of con not implemented\n");
  //return ((struct sem_rec *) NULL);

}

/*
 * dobreak - break statement
 *
 * Grammar:
 * stmt -> BREAK ';'                { dobreak(); }
 *
 * LLVM API calls:
 * None -- but uses n
 */
void
dobreak()
{
  fprintf(stderr, "dobreak: entered\n");

  lscopes[looplevel++].breaks = n();
  //fprintf(stderr, "sem: dobreak not implemented\n");
  //return;
}

/*
 * docontinue - continue statement
 *
 * Grammar:
 * stmt -> CONTINUE ';'              { docontinue(); }
 *
 * LLVM API calls:
 * None -- but uses n
 */
void
docontinue()
{
  fprintf(stderr, "docontinue: entered\n");

  lscopes[looplevel++].conts = n();

  //n();
  //fprintf(stderr, "sem: docontinue not implemented\n");
  //return;
}

/*
 * dodo - do statement
 *
 * Grammar:   m1                    m2 cond         m3
 * stmt -> DO m s lblstmt WHILE '(' m cexpr ')' ';' m
 *                { dodo($2, $7, $8, $11); }
 *
 * LLVM API calls:
 * None -- but uses backpatch
 */
void
dodo(void *m1, void *m2, struct sem_rec *cond, void *m3)
{
  startloopscope();

  backpatch(cond->s_true, m1);
  backpatch(cond->s_false, m2);

  looptop = &lscopes[looplevel];
  backpatch(looptop->conts, m1);
  backpatch(looptop->breaks, m3);
  
  endloopscope();


  //fprintf(stderr, "sem: dodo not implemented\n");
  //return;
}

/*
 * dofor - for statement
 *
 * Grammar:                  m1 cond      m2      n1    m3          n2 m4
 * stmt -> FOR '(' expro ';' m cexpro ';' m expro n ')' m s lblstmt n m
 *               { dofor($5, $6, $8, $10, $12, $15, $16); }
 *
 * LLVM API calls:
 * None -- but uses backpatch
 */
void
dofor(void *m1, struct sem_rec *cond, void *m2, struct sem_rec *n1, void *m3,
  struct sem_rec *n2, void *m4)
{

  if(lscopes[looplevel].breaks){
    cond->s_false = merge(lscopes[looplevel].breaks, cond->s_false);    
  }
  if(lscopes[looplevel].conts){
    n1 = merge(lscopes[looplevel].conts, n1);    
  }

  backpatch(cond->s_true, m3);
  backpatch(cond->s_false, m4);
  backpatch(n1, m1);
  backpatch(n2, m2);

  endloopscope();

  //fprintf(stderr, "sem: dofor not implemented\n");
  //return;
}

/*
 * dogoto - goto statement
 *
 * Grammar:
 * stmt -> GOTO ID ';'              { dogoto($2); }
 *
 * LLVM API calls:
 * IRBuilder::CreateBr(BasicBlock *)
 */
void
dogoto(char *id)
{
  fprintf(stderr, "dogoto - entered\n");

  std::string _label = ((string)id);

  BasicBlock *B = create_named_label(_label);

  Builder.CreateBr(B);

  fprintf(stderr, "dogoto - all good\n");
  //fprintf(stderr, "sem: dogoto not implemented\n");
  return;
}

/*
 * doif - one-arm if statement
 *
 * Grammar:        cond     m1        m2
 * stmt -> IF '(' cexpr ')' m lblstmt m
 *         { doif($3, $5, $7); }
 *
 * LLVM API calls:
 * None -- but uses backpatch
 */
void
doif(struct sem_rec *cond, void *m1, void *m2)
{

  if(lscopes[looplevel].breaks){
    cond->s_false = merge(lscopes[looplevel].breaks, cond->s_false);    
  }
  if(lscopes[looplevel].conts){
    cond->s_true = merge(lscopes[looplevel].conts, cond->s_true);
  }  
  backpatch(cond->s_true, m1);
  backpatch(cond->s_false,m2);

  endloopscope();
  //fprintf(stderr, "sem: doif not implemented\n");
  //return;
}

/*
 * doifelse - if then else statement
 *
 * Grammar:        cond     m1             n m2        m3
 * stmt -> IF '(' cexpr ')' m lblstmt ELSE n m lblstmt m
 *                { doifelse($3, $5, $8, $9, $11); }
 *
 * LLVM API calls:
 * None -- but uses backpatch
 */
void
doifelse(struct sem_rec *cond, void *m1, struct sem_rec *n,
  void *m2, void *m3)
{
  if(lscopes[looplevel].breaks){
    n = merge(n,lscopes[looplevel].breaks);
  }
  if(lscopes[looplevel].conts){
    cond->s_true = merge(cond->s_true, lscopes[looplevel].conts);    
  }

  backpatch(cond->s_true, m1);
  backpatch(cond->s_false, m2);
  backpatch(n, m3);

  endloopscope();
  //fprintf(stderr, "sem: doifelse not implemented\n");
  //return;
}

/*
 * doret - return statement
 *
 * Grammar:
 * stmt -> RETURN ';'            { doret((struct sem_rec *) NULL); }
 * stmt -> RETURN expr ';'       { doret($2); }
 *
 * LLVM API calls:
 * IRBuilder::CreateRetVoid();
 * IRBuilder::CreateRet(Value *);
 */
void
doret(struct sem_rec *e)
{

  fprintf(stderr, "doret: is called\n");
  if(!e){
    Builder.CreateRetVoid();
    return;
  }

  Builder.CreateRet(((Value*) e->s_value));
  //fprintf(stderr, "sem: doret not implemented\n");
  //return;
}

/*
 * dowhile - while statement
 *
 * Grammar:          m1 cond     m2          n m3
 * stmt -> WHILE '(' m cexpr ')' m s lblstmt n m
 *                { dowhile($3, $4, $6, $9, $10); }
 *
 * LLVM API calls:
 * None -- but uses backpatch
 */
void
dowhile(void *m1, struct sem_rec *cond, void *m2,
  struct sem_rec *n, void *m3)
{

  if(lscopes[looplevel].breaks){
    cond->s_false = merge(lscopes[looplevel].breaks, cond->s_false);    
  }
  if(lscopes[looplevel].conts){
    n = merge(n,lscopes[looplevel].conts);
  }


  backpatch(cond->s_true, m2);
  backpatch(cond->s_false, m3);
  backpatch(n, m1);  

  endloopscope();

  //fprintf(stderr, "sem: dowhile not implemented\n");
  //return;
}

/*
 * exprs - form a list of expressions
 *
 * Grammar:
 * exprs -> exprs ',' expr        { $$ = exprs($1, $3); }
 *
 * LLVM API calls:
 * None
 */
struct sem_rec*
exprs(struct sem_rec *l, struct sem_rec *e)
{

    struct sem_rec *LIST;
    
    LIST = l;
    while (l->s_link)
        l = l->s_link;
    l->s_link = e;
    e->s_link = NULL;
    return LIST;
    

    //return merge(l,e);

  //fprintf(stderr, "sem: exprs not implemented\n");
  //return ((struct sem_rec *) NULL);
}

/*
 * fhead - beginning of function body
 *
 * Grammar:
 * fhead -> fname fargs '{' dcls  { fhead($1); }
 */
void
fhead(struct id_entry *p)
{
  Type *func_type, *var_type;
  Value *arr_size;
  vector<Type*> func_args;
  GlobalValue::LinkageTypes linkage;
  FunctionType *FT;
  Function *F;
  BasicBlock *B;
  int i;
  struct id_entry *v;

  /* get function return type */
  func_type = (p->i_type == T_DOUBLE)       ?
              Type::getDoubleTy(TheContext) :
              Type::getInt32Ty(TheContext)  ;

  /* get function argument types */
  for (i = 0; i < formalnum; i++) {
    if (formalvars[i]->i_type == T_DOUBLE) {
      func_args.push_back(Type::getDoubleTy(TheContext));
    } else {
      func_args.push_back(Type::getInt32Ty(TheContext));
    }
  }

  FT = FunctionType::get(func_type, makeArrayRef(func_args), false);

  /* linkage is external if function is main */
  linkage = (strcmp(p->i_name, "main") == 0) ?
            Function::ExternalLinkage :
            Function::InternalLinkage ;

  F = Function::Create(FT, linkage, p->i_name, TheModule.get());
  p->i_value = (void*) F;


  B = BasicBlock::Create(TheContext, "", F);
  Builder.SetInsertPoint(B);

  /* 
   * Allocate instances of each parameter and local so they can be referenced
   * and mutated.
   */
  i = 0;
  for (auto &arg : F->args()) {

    v = formalvars[i++];
    arg.setName(v->i_name);
    var_type = (v->i_type == T_DOUBLE) ?
                Type::getDoubleTy(TheContext) :
                Type::getInt32Ty(TheContext);
    arr_size = (v->i_width > 1) ? 
               (ConstantInt::get(Type::getInt32Ty(TheContext), v->i_width)) :
               NULL;

    v->i_value = Builder.CreateAlloca(var_type, arr_size, arg.getName());

    Builder.CreateStore(&arg, (Value*)v->i_value);
  }

  /* Create the instance of stack memory for each local variable */
  for (i = 0; i < localnum; i++) {
    v = localvars[i];
    var_type = (v->i_type & T_DOUBLE) ?
                Type::getDoubleTy(TheContext) :
                Type::getInt32Ty(TheContext);
    arr_size = (v->i_width > 1) ? 
               (ConstantInt::get(Type::getInt32Ty(TheContext), v->i_width)) :
               NULL;

    v->i_value = Builder.CreateAlloca(var_type, arr_size, std::string(v->i_name));
  }
}

/*
 * fname - function declaration
 *
 * Grammar:
 * fname -> type ID               { $$ = fname($1, $2); }
 * fname -> ID                    { $$ = fname(T_INT, $1); }
 */
struct id_entry*
fname(int t, char *id)
{
  struct id_entry *entry = lookup(id, 0);

  // add function to hash table if it doesn't exist 
  if (!entry) {
    entry = install(id, 0);
  }

  // cannot have two functions of the same name
  if (entry->i_defined) {
    yyerror("cannot declare function more than once");
  }

  entry->i_type = t;
  entry->i_scope = GLOBAL;
  entry->i_defined = true;

  // need to enter the block to let hash table do internal work
  enterblock();
  // then need to reset argument count variables

  formalnum = 0;
  localnum = 0;

  return entry;
}

/*
 * ftail - end of function body
 *
 * Grammar:
 * func -> fhead stmts '}'       { ftail(); }
 */
void
ftail()
{
  numgotos = 0;
  numlabelids = 0;
  leaveblock();
}

/*
 * id - variable reference
 *
 * Grammar:
 * lval -> ID                    { $$ = id($1); }
 * lval -> ID '[' expr ']'       { $$ = indx(id($1), $3); }
 *
 * LLVM API calls:
 * None
 */
struct sem_rec*
id(char *x)
{
  struct id_entry *entry;
  
  if ((entry = lookup(x, 0)) == NULL) {
    yyerror("undeclared identifier");
    entry = install(x, -1);
    entry->i_type = T_INT;
    entry->i_scope = LOCAL;
    entry->i_defined = 1;
  }

  //fprintf(stderr, "sem: remainder of id not implemented\n");
  //return ((struct sem_rec *) NULL);

  return (s_node( (void *) entry->i_value, entry->i_type|T_ADDR));
}

/*
 * indx - subscript
 * 
 * Grammar:
 * lval -> ID '[' expr ']'       { $$ = indx(id($1), $3); }
 *
 * LLVM API calls:
 * ConstantInt::get(Type *, uint64_t, bool)
 * IntegerType::getInt32Ty(LLVMContext &)
 * makeArrayRef(vector<Value*>)
 * IRBuilder::CreateGEP(Type, Value *, ArrayRef<Value*>)
 */
struct sem_rec*
indx(struct sem_rec *x, struct sem_rec *i)
{

  Value *arr;
  std::vector<Value *> args;
  struct sem_rec *node_ret;
  Type *ty;

  arr = (Value*) x->s_value;


  ty = llvm::dyn_cast<PointerType>((arr)->getType()
                                  ->getScalarType())->getElementType();


  args.push_back((Value*)ConstantInt::get(TheContext, llvm::APInt(32, 0)));
  args.push_back((Value*) i->s_value);

  node_ret = node((Value*) NULL, (void*) NULL, 0,(struct sem_rec*) NULL, (struct sem_rec*) NULL,(struct sem_rec*) NULL); 

  node_ret->s_value = (void*) Builder.CreateGEP(ty, arr, makeArrayRef(args));
  node_ret->s_type = x->s_type;

 
  return node_ret;


  //fprintf(stderr, "sem: indx not implemented\n");
  //return ((struct sem_rec *) NULL);
}

/*
 * labeldcl - process a label declaration
 *
 * Grammar:
 * labels -> ID ':'                { labeldcl($1); }
 * labels -> labels ID ':'         { labeldcl($2); }
 * 
 * NOTE: All blocks in LLVM must have a terminating instruction (i.e., branch
 * or return statement -- fall-throughs are not allowed). This code must
 * ensure that each block ends with a terminating instruction.
 *
 * LLVM API calls:
 * IRBuilder::GetInsertBlock()
 * BasicBlock::getTerminator()
 * IRBuilder::CreateBr(BasicBlock*)
 * IRBuilder::SetInsertPoint(BasicBlock*)
 * BranchInst::setSuccessor(unsigned, BasicBlock*)
 */
void
labeldcl(const char *id)
{

fprintf(stderr, "labeldcl - entered label=%s \n",id); 
  BasicBlock *bb;
  Value *val;

  std::string _label = ("userlbl_" + (string)id);

  bb = create_named_label(_label);
  val = Builder.CreateBr(bb); // insert branch
  Builder.SetInsertPoint(bb);
  struct sem_rec* n_node = s_node((Value*)bb, T_LBL);
  for(int i=0;i<label_index; i++){
    if(id == labels[i].id){
      struct sem_rec* l_node =s_node((Value*)labels[i].bb, T_LBL);
      backpatch(l_node, bb);
    }
  }
  return;

}

/*
 * m - generate label and return next temporary number
 *
 * NOTE: All blocks in LLVM must have a terminating instruction (i.e., branch
 * or return statement -- fall-throughs are not allowed). This code must
 * ensure that each block ends with a terminating instruction.
 *
 * LLVM API calls:
 * IRBuilder::GetInsertBlock()
 * BasicBlock::getTerminator()
 * IRBuilder::CreateBr(BasicBlock*)
 * IRBuilder::SetInsertPoint(BasicBlock*)
 */
void*
m ()
{
  BasicBlock *bb;
  std::string label = new_label();
  bb = create_named_label(label);

fprintf(stderr, "m() is called ");


  if(Builder.GetInsertBlock()->getTerminator() == NULL){
    Builder.CreateBr(bb); // insert branch
  }

  Builder.SetInsertPoint(bb);
  return (void *) bb;

  //fprintf(stderr, "sem: m not implemented\n");
  //return (void *) NULL;
}

/*
 * n - generate goto and return backpatch pointer
 *
 * LLVM API calls:
 * IRBuilder::CreateBr(BasicBlock *)
 */
struct sem_rec *n()
{

  Value *val;
  BasicBlock *bb;

  bb = create_tmp_label();
  struct sem_rec* node_ret = nullptr;


  fprintf(stderr, "n() is called ");

  val = Builder.CreateBr(bb); // insert branch
  
  node_ret = node(val,bb, 0,(struct sem_rec*) NULL, (struct sem_rec*) NULL,(struct sem_rec*) NULL); 

  return node_ret;
  
  //fprintf(stderr, "sem: n not implemented\n");
  //return NULL;
}

/*
 * op1 - unary operators
 *
 * LLVM API calls:
 * IRBuilder::CreateLoad(Type, Value *)
 * IRBuilder::CreateNot(Value *)
 * IRBuilder::CreateNeg(Value *)
 * IRBuilder::CreateFNeg(Value *)
 */
struct sem_rec*
op1(const char *op, struct sem_rec *y)
{
  Type *ty;
  
  
  fprintf(stderr, "op1: is called\n");

  struct sem_rec *rec = nullptr;
  switch(*op){
    case '@':
      if (!(y->s_type & T_ARRAY)){
        fprintf(stderr, "op1: @ is called\n");
          ty = llvm::dyn_cast<PointerType>(((Value*)y->s_value)->getType()
                                  ->getScalarType())->getElementType();
        y->s_type &= ~T_ADDR;
        fprintf(stderr, "op1: create load is going to be called\n");
        rec = s_node ( Builder.CreateLoad ( ty, ((Value*)y->s_value) ), y->s_type);
        fprintf(stderr, "op1: create load is called\n");
      }
      else{
      fprintf(stderr, "op1: @ is called for array\n");
       rec = y;
      }
      break;
    case '~':
      rec = s_node ( Builder.CreateNot ( ((Value*)y->s_value) ), y->s_type);
      break;
    case '-':
      if(y->s_type & T_INT){
        rec = s_node ( Builder.CreateNeg ( ((Value*)y->s_value) ), y->s_type);
      }else{
        rec = s_node ( Builder.CreateFNeg ( ((Value*)y->s_value) ), y->s_type);
      }
      break;
    default:
      fprintf(stderr, "sem: op1 %s not implemented\n", op);
      rec = ((struct sem_rec *) NULL);
      break;
  }
  fprintf(stderr, "op1: says bye bye\n");
  return rec;
}

Value*
llvm_op2 (const char *op, int type, Value *L, Value *R)
{
    switch (*op) {
        case '+':
            if (type == T_DOUBLE)
                return Builder.CreateFAdd(L, R, "addtmp");
            else
                return Builder.CreateAdd(L, R, "addtmp");
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
        case '&&':
              return Builder.CreateAnd(L, R, "andtmp");
            break;
        case '||':
            return Builder.CreateOr(L, R, "ortmp");
            break;
        case '^':
            return Builder.CreateXor(L, R, "xortmp");
            break;
        case '<<':
            return Builder.CreateShl(L, R, "shltmp");
            break;
        case '>>':
            return Builder.CreateAShr(L, R, "shrtmp");
            break;

        default:
           fprintf(stderr, "sem: op2 %s not implemented\n", op);
           return NULL;
    }
}

/*
 * op2 - arithmetic operators
 *
 * No LLVM API calls, but most functionality is abstracted to a separate
 * method used by op2, opb, and set.
 *
 * The separate method uses the following API calls:
 * IRBuilder::CreateAdd(Value *, Value *)
 * IRBuilder::CreateFAdd(Value *, Value *)
 * IRBuilder::CreateSub(Value *, Value *)
 * IRBuilder::CreateFSub(Value *, Value *)
 * IRBuilder::CreateMul(Value *, Value *)
 * IRBuilder::CreateFMul(Value *, Value *)
 * IRBuilder::CreateSDiv(Value *, Value *)
 * IRBuilder::CreateFDiv(Value *, Value *)
 * IRBuilder::CreateSRem(Value *, Value *)
 * IRBuilder::CreateAnd(Value *, Value *)
 * IRBuilder::CreateOr(Value *, Value *)
 * IRBuilder::CreateXOr(Value *, Value *)
 * IRBuilder::CreateShl(Value *, Value *)
 * IRBuilder::CreateAShr(Value *, Value *)
 */
struct sem_rec*
op2(const char *op, struct sem_rec *x, struct sem_rec *y)
{
  Value *L, *R;

  L = (Value*) x->s_value;
  R = cast_Rval(y, x->s_type);

  x->s_value = (void*) llvm_op2(op, y->s_type, L, R);
  
  return x;


  //fprintf(stderr, "sem: op2 not implemented\n");
  //return NULL;
}

/*
 * opb - bitwise operators
 *
 * No LLVM API calls, but most functionality is abstracted to a separate
 * method used by op2, opb, and set. The comment above op2 lists the LLVM API
 * calls for this method.
 */
struct sem_rec*
opb(const char *op, struct sem_rec *x, struct sem_rec *y)
{

  Value *L, *R;

  L = (Value*) x->s_value;
  R = cast_Rval(y, x->s_type);

  fprintf(stderr, "opb | doing something");

  x->s_value = (void*) llvm_op2(op, x->s_type, L, R);

  return x;

  //fprintf(stderr, "sem: opb not implemented\n");
  //return ((struct sem_rec *) NULL);
}

/*
 * rel - relational operators
 *
 * Grammar:
 * cexpr -> expr EQ expr          { $$ = rel((char*) "==", $1, $3); }
 * cexpr -> expr NE expr          { $$ = rel((char*) "!=", $1, $3); }
 * cexpr -> expr LE expr          { $$ = rel((char*) "<=", $1, $3); }
 * cexpr -> expr GE expr          { $$ = rel((char*) ">=", $1, $3); }
 * cexpr -> expr LT expr          { $$ = rel((char*) "<",  $1, $3); }
 * cexpr -> expr GT expr          { $$ = rel((char*) ">",  $1, $3); }
 *
 * LLVM API calls:
 * IRBuilder::CreateICmpEq(Value *, Value *)
 * IRBuilder::CreateFCmpOEq(Value *, Value *)
 * IRBuilder::CreateICmpNE(Value *, Value *)
 * IRBuilder::CreateFCmpONE(Value *, Value *)
 * IRBuilder::CreateICmpSLT(Value *, Value *)
 * IRBuilder::CreateFCmpOLT(Value *, Value *)
 * IRBuilder::CreateICmpSLE(Value *, Value *)
 * IRBuilder::CreateFCmpOLE(Value *, Value *)
 * IRBuilder::CreateICmpSGT(Value *, Value *)
 * IRBuilder::CreateFCmpOGT(Value *, Value *)
 * IRBuilder::CreateICmpSGE(Value *, Value *)
 * IRBuilder::CreateFCmpOGE(Value *, Value *)
 */
struct sem_rec*
rel(const char *op, struct sem_rec *x, struct sem_rec *y)
{

  Value *L, *R, *val;

  L = (Value*) x->s_value;
  R = cast_Rval(y, x->s_type);

  switch (*op) {
    case '=':
        
      if ((x->s_type & T_INT))
          val = Builder.CreateICmpEQ(L, R);
      else
          val = Builder.CreateFCmpOEQ(L, R);
      break;
        
    case '!':
  
      if ((x->s_type & T_INT)){
          Value *zero = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
          val = Builder.CreateICmpNE(L, zero);
      }else if (x->s_type & T_DOUBLE){
          Value *zero = llvm::ConstantInt::get(Type::getDoubleTy(TheContext), 0);
          val = Builder.CreateFCmpONE(L, zero);
      }
      break;
    
    case '>':
      if (op[1] == '\0') {
          if ((x->s_type & T_INT))
              val = Builder.CreateICmpSGT(L, R);
          else
              val = Builder.CreateFCmpOGT(L, R);
      }
      else {
          if ((x->s_type & T_INT))
              val = Builder.CreateICmpSGE(L, R);
          else
              val = Builder.CreateFCmpOGE(L, R);
      }
      break;
    case '<':

      if (op[1] == '\0') {
          if (x->s_type & T_INT)
              val = Builder.CreateICmpSLT(L, R);
          else
              val = Builder.CreateFCmpOLT(L, R);
      }
      else {
          if (x->s_type & T_INT)
              val = Builder.CreateICmpSLE(L, R);
          else
              val = Builder.CreateFCmpOLE(L, R);
      }
      break;
    default:
        fprintf(stderr, "sem: rel %s not implemented\n", op);
        return NULL;
  }

  return (ccexpr ( s_node ((void*) val, x->s_type)));

  //fprintf(stderr, "sem: rel not implemented\n op[1] = %s", op[1]);
  //return ((struct sem_rec *) NULL);
}

/*
 * set - assignment operators
 *
 * Grammar:
 * expr -> lval SET expr         { $$ = set((char*) "",   $1, $3); }
 * expr -> lval SETOR expr       { $$ = set((char*) "|",  $1, $3); }
 * expr -> lval SETXOR expr      { $$ = set((char*) "^",  $1, $3); }
 * expr -> lval SETAND expr      { $$ = set((char*) "&",  $1, $3); }
 * expr -> lval SETLSH expr      { $$ = set((char*) "<<", $1, $3); }
 * expr -> lval SETRSH expr      { $$ = set((char*) ">>", $1, $3); }
 * expr -> lval SETADD expr      { $$ = set((char*) "+",  $1, $3); }
 * expr -> lval SETSUB expr      { $$ = set((char*) "-",  $1, $3); }
 * expr -> lval SETMUL expr      { $$ = set((char*) "*",  $1, $3); }
 * expr -> lval SETDIV expr      { $$ = set((char*) "/",  $1, $3); }
 * expr -> lval SETMOD expr      { $$ = set((char*) "%",  $1, $3); }
 *
 * Much of the functionality in this method is abstracted to a separate method
 * used by op2, opb, and set. The comment above op2 lists the LLVM API calls
 * for this method.
 *
 * Additional LLVM API calls:
 * IRBuilder::CreateLoad(Type, Value *)
 * IRBuilder::CreateStore(Value *, Value *)
 */
struct sem_rec*
set(const char *op, struct sem_rec *x, struct sem_rec *y)
{

  Value *storage, *tmp, *value;
  Type *ty;
  struct sem_rec* cast_ret = nullptr;
  struct sem_rec* rec_ret = nullptr;
  struct sem_rec* rec_cl = nullptr;
  
  storage = (Value*) x->s_value;
  value = cast_Rval(y, x->s_type);

  fprintf(stderr, "set | x->s_type=%d value=%s and storage=%s and op=%s\n", x->s_type, value, storage, op);

  if (*op != '\0') {
    ty = llvm::dyn_cast<PointerType>(((Value*)storage)->getType()
                                    ->getScalarType())->getElementType();
    tmp = Builder.CreateLoad(ty, storage, x->s_type);
      value = llvm_op2(op, x->s_type, tmp, value);
  }

  Builder.CreateStore(value, storage);
  x->s_value = (Value*) value;
  return x;

}

/*
 * genstring - generate code for a string
 *
 * Grammar:
 * expr ->  STR                   { $$ = genstring($1); }
 *
 * Use parse_escape_chars (in semutil.c) to handle escape characters
 *
 * LLVM API calls:
 * IRBuilder::CreateGlobalStringPtr(char *)
 */
struct sem_rec*
genstring(char *s)
{
  struct sem_rec *ret;

  ret = s_node(parse_escape_chars(s), T_STR);
  ret->s_value = (void*) Builder.CreateGlobalStringPtr(parse_escape_chars(s));
  return ret;  
  //fprintf(stderr, "sem: genstring not implemented\n");
  //return (struct sem_rec *) NULL;

}

void
declare_print ()
{

  fprintf(stderr, "declare_print | is called");
  struct id_entry *entry;
  FunctionType *var_arg;
  Value *F;
  std::string fname = "print";

  /* Add print to our internal data structure */
  var_arg = FunctionType::get(IntegerType::getInt32Ty(TheContext),
                              PointerType::get(Type::getInt8Ty(TheContext), 0), true);
  F = TheModule->getOrInsertFunction(fname, var_arg).getCallee();

  entry = install( slookup(fname.c_str()), 0 );
  entry->i_type = T_INT | T_PROC;
  entry->i_value = (void*) F;
}

void
init_IR ()
{
  TheModule = make_unique<Module>("<stdin>", TheContext);
  declare_print();
}



void
emit_IR ()
{
  TheModule->print(outs(), nullptr);
}