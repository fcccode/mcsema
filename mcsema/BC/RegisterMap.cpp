#include <vector>
#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "mcsema/BC/RegisterMap.h"

#include <llvm/IR/DataLayout.h>
#include <llvm/Support/raw_ostream.h>

namespace mcsema {

void RegisterMap::_addMember(size_t size, llvm::Type *type) {
  std::shared_ptr<Register> reg = std::make_shared<Register>(size, type);
  for (unsigned int i = 0; i < _layout.getTypeAllocSize(type); i++) {
    idx_to_reg.push_back(reg);
  }
  // This design may have issues in the future
  // You do get to know which register is affected, 
  // but you have no indication of which byte was modified
  // since they're all identical in every way
  // I suppose I can keep track of which byte is modified 
  // As I'm walking the instructions...
}
 
void RegisterMap::_recursivelyAddStructMembers(llvm::Type *tp) {
  //LOG(INFO) << *tp << "\n";
  if (llvm::StructType *nstruc = llvm::dyn_cast<llvm::StructType>(tp)) {
    for (unsigned int i = 0; i < nstruc->getNumElements(); i++) {
      llvm::Type *ntyp = nstruc->getElementType(i);
      _recursivelyAddStructMembers(ntyp);
    }
  }
  else if (llvm::CompositeType *comp = llvm::dyn_cast<llvm::CompositeType>(tp)) {
    LOG(INFO) << "Composite type: " << comp << "\n";
    // handle this case, these are mostly arrays
  }
  else {
    LOG(INFO) << "Size is: " << tp->getPrimitiveSizeInBits() << "\n";
    _addMember(tp->getPrimitiveSizeInBits(), tp);
  }
}

std::shared_ptr<Register> RegisterMap::registerAtOffset(unsigned long offset, size_t size) {
  CHECK(offset < idx_to_reg.size());
  return idx_to_reg[offset];
}

RegisterMap *RegisterMap::registerMapForStateStructure(llvm::StructType *target, const llvm::DataLayout &layout) {
  RegisterMap *rmap = new RegisterMap(layout);
  rmap->_recursivelyAddStructMembers(target);
  return rmap;
}

} // namespace mcsema

