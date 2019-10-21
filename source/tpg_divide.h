#ifndef TPG_INSTRUCTIONS_TPGDIVIDE_H_
#define TPG_INSTRUCTIONS_TPGDIVIDE_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_instruction.h"

class DivideInstruction : public Instruction
{
public:
    DivideInstruction(TpgParameters&);
    DivideInstruction(int8, int32, int8);
    ~DivideInstruction();
    bool execute(double*, double*, const TpgParameters&) const;
    bool mutate(TpgParameters&);
    std::string getType() const;
    std::string toString() const;
    std::string toStorage() const;
};

#endif