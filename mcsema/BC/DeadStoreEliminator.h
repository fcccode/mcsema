// DSE - Dead Store Elimination
// Trying not to java this up

#ifndef MCSEMA_BC_DSE_H_
#define MCSEMA_BC_DSE_H_

#include <llvm/Pass.h>
#include <llvm/IR/BasicBlock.h>
#include <assert.h>

#include "mcsema/CFG/CFG.h"
#include "mcsema/BC/RegisterMap.h"

using namespace llvm;

namespace mcsema {

class DeadStoreEliminationPass : public BasicBlockPass {
  RegisterMap *rMap;
  static char ID;

  // use the gep to get def-use chain
  void _attemptDeadLoadRemoval(GetElementPtrInst *gep);
  void _attemptDeadStoreRemoval(GetElementPtrInst *gep);

  public:
  ~DeadStoreEliminationPass();
  DeadStoreEliminationPass(std::string target) : BasicBlockPass(ID) {
    rMap = RegisterMap::registerMapForTarget(target);
    assert(rMap != NULL && "rMap is null");
  }

  virtual bool runOnBasicBlock(BasicBlock &bb);
};

}

#endif // MCSEMA_BC_DSE_H_
