#ifndef TPG_INSTRUCTIONS_TPGCONDITIONAL_H_
#define TPG_INSTRUCTIONS_TPGCONDITIONAL_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_instruction.h"

class ConditionalInstruction : public Instruction
{
public:
    ConditionalInstruction(TpgParameters&);
    ConditionalInstruction(int8, int32, int8);
    ~ConditionalInstruction();
    bool execute(double*, double*, const TpgParameters&) const;
    bool mutate(TpgParameters&);
    std::string getType() const;
    std::string toString() const;
    std::string toStorage() const;
};

#endif