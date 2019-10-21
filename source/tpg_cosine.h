#ifndef TPG_INSTRUCTIONS_TPGCOSINE_H_
#define TPG_INSTRUCTIONS_TPGCOSINE_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_instruction.h"

class CosineInstruction : public Instruction
{
public:
    CosineInstruction(TpgParameters&);
    CosineInstruction(int8, int32, int8);
    ~CosineInstruction();
    bool execute(double*, double*, const TpgParameters&) const;
    bool mutate(TpgParameters&);
    std::string getType() const;
    std::string toString() const;
    std::string toStorage() const;
};

#endif