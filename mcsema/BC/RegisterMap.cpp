#include "mcsema/BC/RegisterMap.cpp"

namespace mcsema {

void RegisterMap::addGroup(RegisterGroup *g) {

}

Regisetr *RegisterMap::registerAtOffset(off_t offset) {
    return NULL;
}

static RegisterMap *RegisterMap::registerMapForTarget(std::string target) {
    // perhaps use polymorphism here, and return x86RegisterMap
    // only issue is, for example, some x86 processors have different caps
    // so I suppose x86RegisterMap can have a cap section.. :(
    
    RegisterMap *map = new RegisterMap();
    
    if (target == "x86") {

      RegisterGroup *gpr = new RegisterGroup("GPR");
      
      gpr->addRegister(new Register("eax", 4));
      gpr->addRegister(new Register("ebx", 4));
      gpr->addRegister(new Register("ecx", 4));
      gpr->addRegister(new Register("edx", 4));
      gpr->addRegister(new Register("esi", 4));
      gpr->addRegister(new Register("edi", 4));
      gpr->addRegister(new Register("esp", 4));
      gpr->addRegister(new Register("ebp", 4));
      gpr->addRegister(new Register("eip", 4));

      map->addGroup(gpr);
    }
    else if (target == "x86_64") {

    }
    // this should be switch/case style
    return NULL;
  }









}
