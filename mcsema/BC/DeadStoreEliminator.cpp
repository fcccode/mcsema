// DeadStoreEliminator.cpp
//

#include <cstdint>
#include <list>
#include <vector>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>

#include "mcsema/BC/DeadStoreEliminator.h" 

namespace mcsema {

char mcsema::DeadStoreEliminationPass::ID = 0;

bool DeadStoreEliminationPass::runOnBasicBlock(BasicBlock &bb) {
	errs() << "[Begin Dead Store Elim on BB]\n";

	for (auto iter = bb.begin(); iter != bb.end(); iter++) {
		Instruction *inst = &*iter;
		
		// get all operations that are pointers
		// if they reference state structure
		// let's determine the register
		for (unsigned int i = 0; i < inst->getNumOperands(); i++) {
			Value *vp = inst->getOperand(i);
			if (vp->getType()->isPointerTy()) {
				errs() << *inst << "\n";
				break;
			}
		}
	}

	errs() << "[End Dead Store Elim on BB]\n";

	return false;
}

}
