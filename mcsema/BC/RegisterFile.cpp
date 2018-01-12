#include <vector>
#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "mcsema/BC/RegisterFile.h"

#include <llvm/IR/DataLayout.h>
#include <llvm/Support/raw_ostream.h>

namespace mcsema {

void RegisterFile::_addMember(size_t size, llvm::Type *type) {
  std::shared_ptr<Register> reg = std::make_shared<Register>(size, type);
  for (unsigned int i = 0; i < _layout.getTypeAllocSize(type); i++) {
    idx_to_reg.push_back(reg);
  }
}
 
void RegisterFile::_recursivelyAddStructMembers(llvm::Type *tp) {

  if (llvm::StructType *nstruc = llvm::dyn_cast<llvm::StructType>(tp)) {
    for (unsigned int i = 0; i < nstruc->getNumElements(); i++) {
      llvm::Type *ntyp = nstruc->getElementType(i);
      _recursivelyAddStructMembers(ntyp);
    }
  }

  else if (llvm::CompositeType *comp = llvm::dyn_cast<llvm::CompositeType>(tp)) {
    LOG(INFO) << "Composite type: " << comp << "\n";

    if (llvm::ArrayType *array = llvm::dyn_cast<llvm::ArrayType>(comp)) {
      uint64_t count = array->getNumElements();
      llvm::Type *elementType = array->getElementType();
      for (uint64_t i = 0; i < count; i++) {
        _recursivelyAddStructMembers(elementType);
      }
    }
  }

  else {
    // primitive type
    _addMember(tp->getPrimitiveSizeInBits(), tp);
  }
}

std::shared_ptr<Register> RegisterFile::registerAtOffset(unsigned long offset, size_t size) {
  CHECK(offset < idx_to_reg.size());
  return idx_to_reg[offset];
}

RegisterFile::RegisterFile(llvm::StructType *target, const llvm::DataLayout &layout) : _layout(layout) {
  _recursivelyAddStructMembers(target);
}

} // namespace mcsema

