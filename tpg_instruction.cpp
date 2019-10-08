
#include "tpg_instruction.h"

#include <functional>

Instruction::Instruction(int8 mode, int32 source, int8 destination, std::function<double*(int8, int32, int8, double*, double*, TpgParameters*)> operation)
{
    this->mode = mode;
    this->source = source;
    this->destination = destination;
    this->operation = operation;
}

bool Instruction::execute(double* inputFeatures, double* registers, TpgParameters* parameters)
{
    return NULL;
}

bool Instruction::mutate(TpgParameters* parameters)
{
    return NULL;
}

std::string* Instruction::toString()
{
    return nullptr;
}
