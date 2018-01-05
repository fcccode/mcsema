
namespace mcsema {
  
//
// TOOD: Move into own file
class RegisterMap {
  // this class almost definitely needs to be made public
  struct Register {
    std::string name;
    size_t size;
    Register(std::string name_, size_t size_) : name(name_), size(size_) { }
  };

  struct RegisterGroup {
    std::string name;
    std::vector<Register *> members;
    RegisterGroup(std::string name_) : name(name_) {}
    void addRegister(Register *r) {
      members.push_back(r);
    }
  };

  void addGroup(RegisterGroup *g) {
    // makes sense to flatten the group here
    // also makes sense to make this one large template

  }

  Register *registerAtOffset(off_t offset) {
    // depending on how efficient we want this to be
    // we'll have to make some changes
    return NULL;
  }

  public:
  static RegisterMap *registerMapForTarget(std::string target) {
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
};

}
