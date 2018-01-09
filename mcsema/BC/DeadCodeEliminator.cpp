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
  return false;
}

bool DeadCodeEliminationPass::runOnBasicBlock(llvm::BasicBlock &bb) {
  LOG(INFO) << "[Begin Dead Store Elim on BB]\n";

  for (auto iter = bb.begin(); iter != bb.end(); iter++) {
    llvm::Instruction *inst = &*iter;
    
    // get all operations that are pointers
    // if they reference state structure
    // let's determine the register
    if (llvm::GetElementPtrInst *gep = llvm::dyn_cast<llvm::GetElementPtrInst>(inst)) {
      // should maybe also check regular instructions
      // for ops that may reference this?
      llvm::Value *vb = gep->getPointerOperand();
      if (llvm::Argument *glob = llvm::dyn_cast<llvm::Argument>(vb)) {
        LOG(INFO) << "Found Arg: " << "\n";
        // ensure here that this referes to the State structure
        // glob->getName() and glob->getValueName() don't return
        // what I want. 
        _attemptDeadLoadRemoval(gep);
        _attemptDeadCodeRemoval(gep);
      }
    }

    //for (unsigned int i = 0; i < inst->getNumOperands(); i++) {
    //  Value *vp = inst->getOperand(i);
    //  if (vp->getType()->isPointerTy()) {
    //    // check if references state structure
    //    // if so, let's move forward 
    //    //errs() << "[" << vp->getName() << "]\n";
    //    break;
    //  }
    //}
  }

  LOG(INFO) << "[End Dead Store Elim on BB]\n";

  return false;
}

void DeadCodeEliminationPass::_attemptDeadLoadRemoval(llvm::GetElementPtrInst *gep) {
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

void DeadCodeEliminationPass::_attemptDeadCodeRemoval(llvm::GetElementPtrInst *gep) {

}

}
