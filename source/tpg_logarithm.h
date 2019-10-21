#ifndef TPG_INSTRUCTIONS_TPGLOGARITHM_H_
#define TPG_INSTRUCTIONS_TPGLOGARITHM_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_instruction.h"

class LogarithmInstruction : public Instruction
{
public:
    LogarithmInstruction(TpgParameters&);
    LogarithmInstruction(int8, int32, int8);
    ~LogarithmInstruction();
    bool execute(double*, double*, const TpgParameters&) const;
    bool mutate(TpgParameters&);
    std::string getType() const;
    std::string toString() const;
    std::string toStorage() const;
};

#endif