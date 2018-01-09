#include <vector>
#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "mcsema/BC/RegisterMap.h"

#include <llvm/Support/raw_ostream.h>

namespace mcsema {

void RegisterMap::_addMember(size_t size, llvm::Type *typehint) {
  Register *rn = new Register(size, NULL);
  _registers.push_back(rn);
}
 
void RegisterMap::_recursivelyAddStructMembers(llvm::Type *tp) {
  LOG(INFO) << *tp << "\n";
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
    _addMember(tp->getPrimitiveSizeInBits(), NULL);
  }

//  for (unsigned int i = 0; i < struc->getNumElements(); i++) {
//    llvm::Type *tp = struc->getElementType(i);
//
//    if (llvm::StructType *nstruc = llvm::dyn_cast<llvm::StructType>(tp)) {
//      LOG(INFO) << "Recursing on: " << nstruc->getName().str() << "\n";
//      _recursivelyAddStructMembers(nstruc);
//    }
//    else if (llvm::CompositeType *comp = llvm::dyn_cast<llvm::CompositeType>(tp)) {
//       LOG(INFO) << "Composite type mayb: " << comp << "\n";
//
//
//    }
//    else {
//      LOG(INFO) << *tp << "\n";
//      LOG(INFO) << "\t" << tp->getPrimitiveSizeInBits() << "\n";
//    }
//  }
//  LOG(INFO) << "drop\n";
}

Register *RegisterMap::registerAtOffset(off_t offset, size_t size) {
  // do I need a size? also if I end up unaligned with a larger size
  // do I throw an error?
  return NULL;
}

RegisterMap *RegisterMap::registerMapForStateStructure(llvm::StructType *target) {
  RegisterMap *rmap = new RegisterMap();
  rmap->_recursivelyAddStructMembers(target);
  return rmap;
}

} // namespace mcsema

