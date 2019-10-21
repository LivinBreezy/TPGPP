#ifndef TPG_INSTRUCTIONS_TPGEXP_H_
#define TPG_INSTRUCTIONS_TPGEXP_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_instruction.h"

class ExpInstruction : public Instruction
{
public:
    ExpInstruction(TpgParameters&);
    ExpInstruction(int8, int32, int8);
    ~ExpInstruction();
    bool execute(double*, double*, const TpgParameters&) const;
    bool mutate(TpgParameters&);
    std::string getType() const;
    std::string toString() const;
    std::string toStorage() const;
};

#endif