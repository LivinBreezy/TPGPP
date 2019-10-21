#ifndef TPG_INSTRUCTIONS_TPGMULTIPLY_H_
#define TPG_INSTRUCTIONS_TPGMULTIPLY_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_instruction.h"

class MultiplyInstruction : public Instruction
{
public:
    MultiplyInstruction(TpgParameters&);
    MultiplyInstruction(int8, int32, int8);
    ~MultiplyInstruction();
    bool execute(double*, double*, const TpgParameters&) const;
    bool mutate(TpgParameters&);
    std::string getType() const;
    std::string toString() const;
    std::string toStorage() const;
};

#endif