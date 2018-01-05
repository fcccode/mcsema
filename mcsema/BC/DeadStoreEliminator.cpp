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
		errs() << *iter << "\n";
	}

	errs() << "[End Dead Store Elim on BB]\n";

	return false;
}

}
