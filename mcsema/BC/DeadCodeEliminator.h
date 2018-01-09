// DSE - Dead Store Elimination
// Trying not to java this up

#ifndef MCSEMA_BC_DSE_H_
#define MCSEMA_BC_DSE_H_

#include <llvm/Pass.h>
#include <llvm/IR/BasicBlock.h>
#include <assert.h>

#include "mcsema/CFG/CFG.h"
#include "mcsema/BC/RegisterFile.h"

namespace mcsema {

class DeadCodeEliminationPass : public llvm::ModulePass {
  RegisterFile *rMap;
  static char ID;

  void AnalyzeBasicBlock(llvm::BasicBlock &bb);
  // use the gep to get def-use chain
  void AttemptDeadLoadRemoval(llvm::GetElementPtrInst *gep);
  void AttemptDeadStoreRemoval(llvm::GetElementPtrInst *gep);

  public:
  ~DeadCodeEliminationPass();
  DeadCodeEliminationPass(llvm::Module &mod) : llvm::ModulePass(ID) {
    llvm::StructType *state = mod.getTypeByName("struct.State");
    rMap = new RegisterFile(state, mod.getDataLayout());
  }

  virtual bool runOnModule(llvm::Module &mod);
};

} // namespace mcsema

#endif // MCSEMA_BC_DSE_H_
