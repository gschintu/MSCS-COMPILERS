#include "llvm/Pass.h"
#include "llvm/IR/Instructions.h"
#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/CommandLine.h"

#include <map>
#include <vector>
#include <string>
#include <set>
#include <queue>

#define SRC_IDX 0
#define DST_IDX 1

using namespace llvm;
using namespace std;

typedef map<Value*, Value*> ACPTable;

class BasicBlockInfo {
  public:
    BitVector COPY;
    BitVector KILL;
    BitVector CPIn;
    BitVector CPOut;
    ACPTable  ACP;
    
    BasicBlockInfo(unsigned int max_copies)
    {
        COPY.resize(max_copies);
        KILL.resize(max_copies);
        CPIn.resize(max_copies);
        CPOut.resize(max_copies);
    }
};

namespace {
class CopyPropagation : public FunctionPass
{
  private:
    void localCopyPropagation( Function &F );
    void globalCopyPropagation( Function &F );
    void propagateCopies(BasicBlock &bb, ACPTable &acp);

  public:
    static char ID;
    static cl::opt<bool> verbose;
    CopyPropagation() : FunctionPass( ID ) {}

    bool runOnFunction( Function &F ) override
    {
        localCopyPropagation( F );
        globalCopyPropagation( F );
        return true;
    }
}; // end CopyPropagation

class DataFlowAnalysis
{
    private:
        /* LLVM does not store the position of instructions in the Instruction
         * class, so we create maps of the store instructions to make them
         * easier to use and reference in the BitVector objects
         */
        std::vector<Value*> copies;
        std::map<Value*, int> copy_idx;
        std::map<int, Value*> idx_copy;
        std::map<BasicBlock*, BasicBlockInfo*> bb_info;
        unsigned int nr_copies;

        void addCopy(Value *v);
        void initCopyIdxs(Function &F);
        void initCOPYAndKILLSets(Function &F);
        void initCPInAndCPOutSets(Function &F);
        void initACPs();

    public:
        DataFlowAnalysis(Function &F);
        ACPTable &getACP(BasicBlock &bb);
        void printCopyIdxs();
		void printDFA();

}; //end DataFlowAnalysis
}  // end anonymous namespace

char CopyPropagation::ID = 0;
static RegisterPass<CopyPropagation> X("copy_prop", "copy_prop",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

cl::opt<bool> CopyPropagation::verbose( "verbose", cl::desc( "turn on verbose printing" ), cl::init( false ) );


/*
 * propagateCopies performs copy propagation over the block bb using the
 * available copy instructions in the table acp. It will also remove load
 * instructions if they are no longer useful.
 *
 * Useful tips:
 *
 * Use C++ features to iterate over the instructions in a block, e.g.:
 *   Instruction *iptr;
 *   for (Instruction &ins : bb) {
 *     iptr = &ins;  
 *     ...
 *   }
 *
 * You can use isa to determine the type of an instruction, e.g.:
 *   if (isa<StoreInst>(iptr)) {
 *     // iptr points to an Instruction that is a StoreInst
 *   }
 *
 * Other useful LLVM routines:
 *   int  Instruction::getOperand(int)
 *   void Instruction::setOperand(int)
 *   int  Instruction::getNumOperands()
 *   void Instruction::eraseFromParent()
 */
void CopyPropagation::propagateCopies(BasicBlock &bb, ACPTable &acp) {
    std::vector<Instruction *> toRemove; // A set of instructions to be removed

    // Iterate over the instructions in the basic block
    for (Instruction &ins : bb) {
        if (isa<StoreInst>(ins)) {
            StoreInst *store = cast<StoreInst>(&ins);
            Value *src = store->getValueOperand();
            Value *dst = store->getPointerOperand();

            // If there's a copy from src in the ACPTable, replace the store's value with the copy
            auto acpEntry = acp.find(src);
            if (acpEntry != acp.end()) {
                Value *copySrc = acpEntry->second;

                // Replace the store's value with the copy's source
                store->setOperand(0, copySrc);

                // Mark the store instruction for removal
                toRemove.push_back(store);
            } else {
                // If the store instruction introduces a new copy, update the ACPTable
                acp[dst] = src;
            }
        } else if (isa<LoadInst>(ins)) {
            LoadInst *load = cast<LoadInst>(&ins);
            Value *src = load->getPointerOperand();

            // If there's a copy from src in the ACPTable, replace the load with the copy
            auto acpEntry = acp.find(src);
            if (acpEntry != acp.end()) {
                Value *copySrc = acpEntry->second;

                // Replace all uses of the loaded value with the copy's source
                load->replaceAllUsesWith(copySrc);

                // Mark the load instruction for removal
                toRemove.push_back(load);
            }
        }
    }

    // Remove the marked instructions from the basic block
    for (Instruction *instr : toRemove) {
        instr->eraseFromParent();
    }
}


/*
 * localCopyPropagation performs local copy propagation (LCP) over the basic
 * blocks in the function F. The algorithm for LCP described on pp. 357-358 in
 * the provided text (Muchnick).
 *
 * Useful tips:
 *
 * Use C++ features to iterate over the blocks in F, e.g.:
 *   for (BasicBlock &bb : F) {
 *     ...
 *   }
 *
 * This routine should call propagateCopies
 */
void CopyPropagation::localCopyPropagation( Function &F )
{

    // Iterate over the basic blocks in the function
    for (BasicBlock &bb : F) {
        // Create an ACPTable for each basic block
        ACPTable acp;

        // Call propagateCopies for each basic block
        propagateCopies(bb, acp);
    }

    if (verbose) {
        errs() << "post local" << "\n" << (*(&F)) << "\n";
    }	
	
}

/*
 * globalCopyPropagation performs global copy propagation (LCP) over the basic
 * blocks in the function F. The algorithm for GCP described on pp. 358-360 in
 * the provided text (Muchnick).
 *
 * Useful tips:
 *
 * This routine will use the DataFlowAnalysis to construct COPY, KILL, CPIn,
 * and CPOut sets and an ACP table for each block.
 *
 * Use C++ features to iterate over the blocks in F, e.g.:
 *   for (BasicBlock &bb : F) {
 *     ...
 *   }
 *
 * This routine should also call propagateCopies
 */
void CopyPropagation::globalCopyPropagation( Function &F )
{
   // Create a DataFlowAnalysis object for the function
	DataFlowAnalysis *dfa;
    dfa = new DataFlowAnalysis(F);

    // Iterate over the basic blocks in the function
    for (BasicBlock &bb : F) {

        // Call propagateCopies with the current basic block and its ACP table
        propagateCopies(bb, dfa->getACP(bb));
    }

    if (verbose) {
        errs() << "post global" << "\n" << F << "\n";
    }
}


/*
 * addCopy is a helper routine for initCopyIdxs. It updates state information
 * to record the index of a single copy instruction
 */
void DataFlowAnalysis::addCopy(Value* v)
{

	// If the value is not already in the copy_idx map, add it with a new index
    if (copy_idx.find(v) == copy_idx.end()) {
        int idx = static_cast<int>(copy_idx.size()); // Get the next available index
        copy_idx[v] = idx;              // Add the value to the map with the index
        idx_copy[idx] = v;              // Update the reverse mapping
        copies.push_back(v);            // Add the value to the copies vector
		nr_copies++;
		
        // Resize CP's sets

		for (auto &entry : bb_info) {
            BasicBlockInfo *bbInfo = entry.second;
            bbInfo->COPY.resize(idx + 1, false);
            bbInfo->KILL.resize(idx + 1, false);
            bbInfo->CPIn.resize(idx + 1, false);
            bbInfo->CPOut.resize(idx + 1, false);
        }
    }
}

/* 
 * initCopyIdxs creates a table that records unique identifiers for each copy
 * (i.e., argument and store) instructions in LLVM.
 *
 * LLVM does not store the position of instructions in the Instruction class,
 * so this routine is used to record unique identifiers for each copy
 * instruction in the Function F. This step makes it easier to identify copy
 * instructions in the COPY, KILL, CPIn, and CPOut sets.
 * 
 * Useful tips:
 *
 * You should record function arguments and store instructions as copy
 * instructions.
 *
 * Some useful LLVM routines in this routine are:
 *   Function::arg_iterator Function::arg_begin()
 *   Function::arg_iterator Function::arg_end()
 *   bool llvm::isa<T>(Instruction *)
 */

void DataFlowAnalysis::initCopyIdxs(Function &F)
{
    // Record function arguments as copy instructions
    for (Function::arg_iterator arg = F.arg_begin(); arg != F.arg_end(); ++arg) {
        addCopy(&*arg);
    }

    // Iterate through the basic blocks in the function
    for (BasicBlock &bb : F) {

		// If the BasicBlockInfo object doesn't exist, create it
		if (bb_info.find(&bb) == bb_info.end()) {
            bb_info[&bb] = new BasicBlockInfo(nr_copies);
		}
		
        // Iterate through the instructions in the basic block
        for (Instruction &ins : bb) {
            // Check if the instruction is a store instruction and record it as a copy instruction
            if (isa<StoreInst>(&ins)) {
				addCopy(&ins);
            }

        }
    }
}



/*
 * initCOPYAndKILLSets initializes the COPY and KILL sets for each basic block
 * in the function F.
 *
 * Useful tips:
 *
 * This routine should visit the blocks in reverse post order. You can use an
 * LLVM iterator to complete this traversal, e.g.:
 *
 *   BasicBlock *bb;
 *   ReversePostOrderTraversal<Function*> RPOT(&F);
 *   for ( auto BB = RPOT.begin(); BB != RPOT.end(); BB++ ) {
 *       bb = *BB;
 *       ...
 *   }
 *
 * This routine should create BasicBlockInfo objects for each basic block and
 * record the BasicBlockInfo for each block in the bb_info map.
 *
 * Some useful LLVM routines in this routine are:
 *   bool llvm::isa<T>(Instruction *)
 *   int  Instruction::getOperand(int)
 */

void DataFlowAnalysis::initCOPYAndKILLSets(Function &F) {
    // Visit the blocks in reverse post-order
    BasicBlock *bb;
    ReversePostOrderTraversal<Function *> RPOT(&F);
    for (auto BB = RPOT.begin(); BB != RPOT.end(); ++BB) {
        bb = *BB;

        // Ensure that the BasicBlockInfo object exists for the current block
        if (bb_info.find(bb) == bb_info.end()) {
            bb_info[bb] = new BasicBlockInfo(nr_copies);
        }
        BasicBlockInfo *bbInfo = bb_info[bb];

        // Iterate over the instructions in the basic block
        for (Instruction &ins : *bb) {
            if (auto *SI = dyn_cast<StoreInst>(&ins)) {
                Value *lhs = SI->getPointerOperand();
                Value *rhs = SI->getValueOperand();

                if (copy_idx.find(SI) != copy_idx.end()) {
                    // If the store instruction is in our set of copies, it's a COPY operation
                    bbInfo->COPY.set(copy_idx[SI]);
                }

                // The LHS of a store instruction can potentially KILL a copy
				// It doesn't work well inside the Instruction loop. Need to review.
				/*
                for (int i = 0; i < nr_copies; i++) {
                    if (auto *otherSI = dyn_cast<StoreInst>(copies[i])) {
                        if (otherSI->getPointerOperand() == lhs && otherSI != SI) {
                           //bbInfo->KILL.set(i);
                        }
                    }
                }
				*/
            }
        }

        // Iterate over the copy_idx and check for additional copies to kill
		// This fixes input 1-3 and many blocks on input 4-6
        for (auto &entry : copy_idx) {
            Value *copy = entry.first;
            int idx = entry.second;

            // Check if the copy exists in the block and should be killed
            if (auto *otherSI = dyn_cast<StoreInst>(copy)) {
                Value *lhs = otherSI->getPointerOperand();
                for (Instruction &ins : *bb) {
                    if (auto *SI = dyn_cast<StoreInst>(&ins)) {
                        Value *otherLHS = SI->getPointerOperand();
                        if (otherLHS == lhs && otherSI != SI && !bbInfo->COPY.test(idx) ) {
                            bbInfo->KILL.set(entry.second);
                            break;
                        }
                    }
                }
            }
        }
    }
}


/*
 * initCPInAndCPOutSets initializes the CPIn and CPOut sets for each basic
 * block in the function F.
 *
 * Useful tips:
 * 
 * Similar to initCOPYAndKillSets, you will need to traverse the blocks in
 * reverse post order.
 *
 * You can iterate the predecessors and successors of a block bb using
 * LLVM-defined iterators "predecessors" and "successors", e.g.:
 *
 *   for ( BasicBlock* pred : predecessors( bb ) ) {
 *       // pred points to a predecessor of bb
 *       ...
 *   }
 *
 * You will need to define a special case for the entry block (and some way to
 * identify the entry block).
 *
 * Use set operations on the appropriate BitVector to create CPIn and CPOut.
 */

void DataFlowAnalysis::initCPInAndCPOutSets(Function &F) {
    // Iterate over the basic blocks in reverse post-order
    ReversePostOrderTraversal<Function *> RPOT(&F);

    bool changed;
    do {
        changed = false;

        for (auto BB = RPOT.begin(); BB != RPOT.end(); ++BB) {
            BasicBlock *bb = *BB;

            // Ensure that the BasicBlockInfo object exists for the current block
            if (bb_info.find(bb) == bb_info.end()) {
                bb_info[bb] = new BasicBlockInfo(nr_copies);
            }

            BasicBlockInfo *bbInfo = bb_info[bb];

            // Save the previous CPIn set for convergence check
            BitVector prevCPIn = bbInfo->CPIn;

            // If the current basic block is the entry block, initialize CPIn to all zeros
            if (bb == &F.getEntryBlock()) {
                bbInfo->CPIn.reset();
            } else {
                // For all other blocks, initialize CPIn to all ones
                bbInfo->CPIn.set();
            }

            // Iterate through the predecessors of the current basic block
            for (BasicBlock *pred : predecessors(bb)) {
                // Get the BasicBlockInfo object for the predecessor block
                BasicBlockInfo *predInfo = bb_info[pred];
				// Calculate CPOut for the predecessor block by applying the data-flow equation
				// CPOut = (CPIn - KILL) U COPY
				BitVector tmpCPOut = predInfo->CPIn;
				tmpCPOut.reset(predInfo->KILL); // Subtract KILL from CPIn
				tmpCPOut |= predInfo->COPY; // Union with COPY

				bbInfo->CPIn &= tmpCPOut; // Intersect with the current CPIn
                
            }

			// Calculate CPOut for the current block by applying the data-flow equation
			// CPOut = (CPIn - KILL) U COPY
			bbInfo->CPOut = bbInfo->CPIn; // Start with CPIn
			bbInfo->CPOut.reset(bbInfo->KILL); // Subtract KILL
			bbInfo->CPOut |= bbInfo->COPY; // Union with COPY

            // Check for convergence: if the CPIn set has changed, set 'changed' to true
            if (bbInfo->CPIn != prevCPIn) {
                changed = true;
            }
        }
    } while (changed);
}

/*
 * initACPs creates an ACP table for each basic block, which will be used to
 * conduct global copy propagation.
 *
 * Useful tips:
 *
 * You will need to use CPIn to determine if a copy should be in the ACP for
 * this block.
 */

void DataFlowAnalysis::initACPs()
{
    // Iterate over the basic block information entries
    for (auto &entry : bb_info) {
        BasicBlock *bb = entry.first;
        BasicBlockInfo *bbInfo = entry.second;

        // Iterate over the copy instructions
        for (size_t i = 0; i < nr_copies; ++i) {
            // If the copy is in CPIn, add it to the ACP table
            if (i < bbInfo->CPIn.size() && bbInfo->CPIn.test(i)) {
                Instruction *storeInst = dyn_cast<Instruction>(copies[i]);

                // Check if storeInst is not null before using it
                if (!storeInst) {
                    continue;
                }

                if (StoreInst *store = dyn_cast<StoreInst>(storeInst)) {
                    // Check if store is not null before using it
                    if (!store) {
                        continue;
                    }

                    Value *allocaInst = store->getPointerOperand();
                    Value *valueStored = store->getValueOperand();
                    bbInfo->ACP[allocaInst] = valueStored;
                }
            }
        }
    }
}


ACPTable &DataFlowAnalysis::getACP(BasicBlock &bb)
{
    return bb_info[(&bb)]->ACP;
}


void DataFlowAnalysis::printCopyIdxs()
{
    errs() << "copy_idx:" << "\n";
    for ( auto it = copy_idx.begin(); it != copy_idx.end(); ++it )
    {
        errs() << "  " << format("%-3d", it->second)
               << " --> " << *( it->first ) << "\n";
    }
    errs() << "\n";
}

void DataFlowAnalysis::printDFA()
{
    unsigned int i;

    // used for formatting
    std::string str;
    llvm::raw_string_ostream rso( str );

    for ( auto it = bb_info.begin(); it != bb_info.end(); ++it )
    {
        BasicBlockInfo *bbi = bb_info[it->first];

        errs() << "BB ";
        it->first->printAsOperand(errs(), false);
        errs() << "\n";

        errs() << "  CPIn  ";
        for ( i = 0; i < bbi->CPIn.size(); i++ )
        {
            errs() << bbi->CPIn[i] << ' ';
        }
        errs() << "\n";

        errs() << "  CPOut ";
        for ( i = 0; i < bbi->CPOut.size(); i++ )
        {
            errs() << bbi->CPOut[i] << ' ';
        }
        errs() << "\n";

        errs() << "  COPY  ";
        for ( i = 0; i < bbi->COPY.size(); i++ )
        {
            errs() << bbi->COPY[i] << ' ';
        }
        errs() << "\n";

        errs() << "  KILL  ";
        for ( i = 0; i < bbi->KILL.size(); i++ )
        {
            errs() << bbi->KILL[i] << ' ';
        }
        errs() << "\n";

        errs() << "  ACP:" << "\n";
        for ( auto it = bbi->ACP.begin(); it != bbi->ACP.end(); ++it )
        {
            rso << *( it->first );
            errs() << "  " << format("%-30s", rso.str().c_str()) << "==  "
                   << *( it->second ) << "\n";
            str.clear();
        }
        errs() << "\n" << "\n";
    }
}

/*
 * DataFlowAnalysis constructs the data flow analysis for the function F.
 *
 * You will not need to modify this routine.
 */
DataFlowAnalysis::DataFlowAnalysis( Function &F )
{
    initCopyIdxs(F);
    initCOPYAndKILLSets(F);
    initCPInAndCPOutSets(F);
    initACPs();

    if (CopyPropagation::verbose) {
        errs() << "post DFA" << "\n";
        printCopyIdxs();
        printDFA();
    }
}

