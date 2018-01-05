#include <vector>
#include <string>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "mcsema/BC/RegisterMap.h"

#include <llvm/Support/raw_ostream.h>

namespace mcsema {

void RegisterMap::_recursivelyAddStructMembers(llvm::StructType *struc) {
  for (unsigned int i = 0; i < struc->getNumElements(); i++) {
    llvm::Type *tp = struc->getElementType(i);
    if (llvm::StructType *nstruc = llvm::dyn_cast<llvm::StructType>(tp)) {
      LOG(INFO) << "Recursing on: " << nstruc->getName().str() << "\n";
      _recursivelyAddStructMembers(nstruc);
    }
    else if (llvm::CompositeType *comp = llvm::dyn_cast<llvm::CompositeType>(tp)) {
       LOG(INFO) << "Composite type mayb: " << comp << "\n";
      // get sizey
    }
  }
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

