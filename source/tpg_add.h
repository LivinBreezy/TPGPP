#ifndef TPG_INSTRUCTIONS_TPGADD_H_
#define TPG_INSTRUCTIONS_TPGADD_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_instruction.h"

class AddInstruction : public Instruction
{
public:
    AddInstruction(TpgParameters&);
    AddInstruction(int8, int32, int8);
    ~AddInstruction();
    bool execute(double*, double*, const TpgParameters&) const;
    bool mutate(TpgParameters&);
    std::string getType() const;
    std::string toString() const;
    std::string toStorage() const;
};

#endif