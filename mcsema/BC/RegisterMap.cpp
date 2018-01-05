#include <vector>
#include <string>

#include "mcsema/BC/RegisterMap.h"

using namespace std;

namespace mcsema {

void RegisterMap::addGroup(RegisterGroup *g) {
  // TOOD: implement this 
  // once internal rep is decided
}

Register *RegisterMap::registerAtOffset(off_t offset, size_t size) {
  // do I need a size? also if I end up unaligned with a larger size
  // do I throw an error?
  return NULL;
}

RegisterMap *RegisterMap::registerMapForTarget(std::string target) {
  // perhaps use polymorphism here, and return x86RegisterMap
  // only issue is, for example, some x86 processors have different caps
  // so I suppose x86RegisterMap can have a cap section.. :(
  
  RegisterMap *map = new RegisterMap();
  // TODO: Add rest of registers...
  // TODO: Add other archs... and cpu feature combinations
  
  if (target == "x86") {
    // XXX: Should `ax`, `al`, et al be their own indep. registers?
    RegisterGroup *gpr = new RegisterGroup("GPR");
    // general purpose registers
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

    RegisterGroup *gpr = new RegisterGroup("GPR");
    // general purpose registers
    gpr->addRegister(new Register("rax", 8));
    gpr->addRegister(new Register("rbx", 8));
    gpr->addRegister(new Register("rcx", 8));
    gpr->addRegister(new Register("rdx", 8));
    gpr->addRegister(new Register("rsi", 8));
    gpr->addRegister(new Register("rdi", 8));
    gpr->addRegister(new Register("rsp", 8));
    gpr->addRegister(new Register("rbp", 8));
    gpr->addRegister(new Register("rip", 8));

    map->addGroup(gpr);
  }
  // this should be switch/case style
  return NULL;
}

}
