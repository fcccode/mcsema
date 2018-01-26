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
 
typedef enum RegisterAccessType {
  RegisterAccessTypeRead,
  RegisterAccessTypeWrite,
} RegisterAccess;

using AccessMask = std::bitset<256>;

struct RegisterActivity {
  std::shared_ptr<Register> reg;
  AccessMask *mask;
  RegisterAccess accessType;
};

class DeadCodeEliminationPass : public llvm::ModulePass {

  RegisterFile *rMap;
  static char ID;
  const llvm::Module &mod;

  void AnalyzeBasicBlock(llvm::BasicBlock &bb);
  // use the gep to get def-use chain
  void AttemptDeadLoadRemoval(llvm::GetElementPtrInst *gep);
  void AttemptDeadStoreRemoval(llvm::GetElementPtrInst *gep);
  bool InstructionTouchesStateStructure(llvm::Instruction &val);
  RegisterAccess GetInstructionAccessType(llvm::Instruction &inst);
  AccessMask *GetInstructionAccessMask(llvm::Instruction &inst);
  std::shared_ptr<Register> GetAccessedRegister(llvm::Instruction &inst);

  public:
  ~DeadCodeEliminationPass();
  DeadCodeEliminationPass(llvm::Module &_mod) : llvm::ModulePass(ID), mod(_mod) {
    llvm::StructType *state = mod.getTypeByName("struct.State");
    rMap = new RegisterFile(state, mod.getDataLayout());
  }

  virtual bool runOnModule(llvm::Module &mod);
};

} // namespace mcsema

#endif // MCSEMA_BC_DSE_H_
