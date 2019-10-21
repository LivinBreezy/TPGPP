#ifndef TPG_INSTRUCTIONS_TPGSUBTRACT_H_
#define TPG_INSTRUCTIONS_TPGSUBTRACT_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_instruction.h"

class SubtractInstruction : public Instruction
{
public:
    SubtractInstruction(TpgParameters&);
    SubtractInstruction(int8, int32, int8);
    ~SubtractInstruction();
    bool execute(double*, double*, const TpgParameters&) const;
    bool mutate(TpgParameters&);
    std::string getType() const;
    std::string toString() const;
    std::string toStorage() const;
};

#endif