// DSE - Dead Store Elimination
// Trying not to java this up

#ifndef MCSEMA_BC_DSE_H_
#define MCSEMA_BC_DSE_H_

#include <llvm/Pass.h>
#include <llvm/IR/BasicBlock.h>
#include <assert.h>

#include "mcsema/CFG/CFG.h"
#include "mcsema/BC/RegisterMap.h"

namespace mcsema {

class DeadCodeEliminationPass : public llvm::ModulePass {
  RegisterMap *rMap;
  static char ID;

  // use the gep to get def-use chain
  void _attemptDeadLoadRemoval(llvm::GetElementPtrInst *gep);
  void _attemptDeadCodeRemoval(llvm::GetElementPtrInst *gep);

  public:
  ~DeadCodeEliminationPass();
  DeadCodeEliminationPass(llvm::Module &mod) : llvm::ModulePass(ID) {
    llvm::StructType *state = mod.getTypeByName("struct.State");
    rMap = RegisterMap::registerMapForStateStructure(state, mod.getDataLayout());
    assert(rMap != NULL && "rMap is null");
  }

  virtual bool runOnModule(llvm::Module &mod);
  virtual bool runOnBasicBlock(llvm::BasicBlock &bb);
};

}

#endif // MCSEMA_BC_DSE_H_
