// DeadCodeEliminator.cpp
//
#include <gflags/gflags.h>
#include <glog/logging.h>

#include <cstdint>
#include <list>
#include <vector>
#include <utility>

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

bool DeadCodeEliminationPass::InstructionTouchesStateStructure(llvm::Instruction &val) {
  // remill::NthArgument
  return false;
}

std::shared_ptr<Register> DeadCodeEliminationPass::GetAccessedRegister(llvm::Instruction &inst) {
  // use access mask to determine this
  return rMap->registerAtOffset(0, 0);
}

RegisterAccess DeadCodeEliminationPass::GetInstructionAccessType(llvm::Instruction &inst) {
  return RegisterAccessTypeRead;;
}

AccessMask *DeadCodeEliminationPass::GetInstructionAccessMask(llvm::Instruction &inst) {
  return new AccessMask("0");
}

void DeadCodeEliminationPass::AnalyzeBasicBlock(llvm::BasicBlock &bb) {
  LOG(INFO) << "[Begin Dead Store Elim on BB]\n";

  std::unordered_map<llvm::Instruction *, RegisterActivity> inst_activity;

  for (auto &inst : bb) {
    if (InstructionTouchesStateStructure(inst)) {
      auto accessType = GetInstructionAccessType(inst);
      auto activity = GetInstructionAccessMask(inst);
      auto reg = GetAccessedRegister(inst);
      inst_activity[&inst].reg = reg;;
      inst_activity[&inst].mask = activity;
      inst_activity[&inst].accessType = accessType;
    }
  }

  // Now we have map from instruction to its access to each register
  // From here, we should create an ordered-array of <AccessType, AccessMask>
  // and map it to each register
  // then just attempt to flatten it, and look for conflicts

  std::vector<llvm::Instruction *> work_list;

  for (auto iter = bb.rbegin(); iter != bb.rend(); iter++) {
    work_list.push_back(&*iter);
  }

  bool made_progress = false;

  std::unordered_map<uint, std::vector<RegisterActivity>> reg_activity;

  do {
    std::vector<llvm::Instruction *> next_work_list;
    for (auto inst : work_list) {
      // TODO: properly use next_work_list

    }

  } while (made_progress);

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
