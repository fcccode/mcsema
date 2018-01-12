// DeadCodeEliminator.cpp
//
#include <gflags/gflags.h>
#include <glog/logging.h>

#include <cstdint>
#include <list>
#include <vector>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

#include "mcsema/BC/DeadCodeEliminator.h" 

namespace mcsema {

char mcsema::DeadCodeEliminationPass::ID = 0;

DeadCodeEliminationPass::~DeadCodeEliminationPass() {
  delete rMap;
}

bool DeadCodeEliminationPass::runOnModule(llvm::Module &mod) {
  for (auto funcIter = mod.begin(); funcIter != mod.end(); funcIter++) {
    for (auto bbIter = funcIter->begin(); bbIter != funcIter->end(); bbIter++) {
      AnalyzeBasicBlock(*bbIter);
    }
  }
  return false;
}

bool DeadCodeEliminationPass::OpRefersToStateStructure(llvm::Value *val) {
  llvm::StructType *state = mod.getTypeByName("struct.State");
  if (val->getType()->getTypeID() == state->getTypeID()) {
    llvm::errs() << "found state\n";
  }
  else {
    // walk def-use
  }
  return false;
}

void DeadCodeEliminationPass::AnalyzeBasicBlock(llvm::BasicBlock &bb) {
  LOG(INFO) << "[Begin Dead Store Elim on BB]\n";

  for (auto iter = bb.begin(); iter != bb.end(); iter++) {
    llvm::Instruction *inst = &*iter;
    
    // get all operations that are pointers
    // if they reference state structure
    // let's determine the register
    if (llvm::GetElementPtrInst *gep = llvm::dyn_cast<llvm::GetElementPtrInst>(inst)) {
      auto operand = gep->getPointerOperand();
      if (OpRefersToStateStructure(operand)) {
        AttemptDeadLoadRemoval(gep);
        AttemptDeadStoreRemoval(gep);
      }
    }
  }

  LOG(INFO) << "[End Dead Store Elim on BB]\n";
}

void DeadCodeEliminationPass::AttemptDeadLoadRemoval(llvm::GetElementPtrInst *gep) {
  // gep->setIsInBounds(true) perhaps 
  
  // get->getResultElementType() to get the size of the access
  // seems like its the last element of gep->indices().begin()
  // for the index
  __attribute__((unused)) std::shared_ptr<Register> efreg = rMap->registerAtOffset(0, 0);
  __attribute__((unused)) std::vector<std::shared_ptr<Register>> useStack;

  for (auto iter = gep->use_begin(); iter != gep->use_end(); iter++) {
    LOG(INFO) << *iter << "\n";
  }
}

void DeadCodeEliminationPass::AttemptDeadStoreRemoval(llvm::GetElementPtrInst *gep) {

}

}
