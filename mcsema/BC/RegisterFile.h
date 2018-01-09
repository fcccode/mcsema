// RegisterFile, handles reflection on State structure
// to access registers based on offsets, get names, etc

#ifndef MCSEMA_BC_REGMAP_H
#define MCSEMA_BC_REGMAP_H

#include <string>

#include <llvm/IR/DataLayout.h>
#include <llvm/IR/DerivedTypes.h>

namespace mcsema {

// what is the scope for this class?
struct Register {
  std::string name;
  size_t size;
  Register(size_t size_, llvm::Type *typehint) : size(size_) { }
};
  
// TODO: Ask Peter his thoughts on this design
// depending on how efficient we want this to be
// we'll have to make some changes
class RegisterFile {

  struct RegisterGroup {
    std::string name;
    std::vector<Register *> members;
    RegisterGroup(std::string name_) : name(name_) {}
    void addRegister(Register *r) { members.push_back(r); }
  };

  std::vector<std::shared_ptr<Register>> idx_to_reg;
  const llvm::DataLayout &_layout;

  void _recursivelyAddStructMembers(llvm::Type *type);
  void _addMember(size_t size, llvm::Type *typehint);

  public:
  std::shared_ptr<Register> registerAtOffset(unsigned long offset, size_t size);
  RegisterFile(llvm::StructType *state_struc, const llvm::DataLayout &layout);
};

}

#endif // MCSEMA_BC_REGMAP_H

