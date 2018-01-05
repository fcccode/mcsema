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

class DeadCodeEliminationPass : public ModulePass {
  RegisterMap *rMap;
  static char ID;

  // use the gep to get def-use chain
  void _attemptDeadLoadRemoval(GetElementPtrInst *gep);
  void _attemptDeadCodeRemoval(GetElementPtrInst *gep);

  public:
  ~DeadCodeEliminationPass();
  DeadCodeEliminationPass() : ModulePass(ID) {
    rMap = RegisterMap::registerMapForTarget("x86");
    assert(rMap != NULL && "rMap is null");
  }

  virtual bool runOnModule(Module &mod);
  virtual bool runOnBasicBlock(BasicBlock &bb);
};

}

#endif // MCSEMA_BC_DSE_H_
