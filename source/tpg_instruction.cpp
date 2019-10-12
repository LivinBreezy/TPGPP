
#include "tpg_instruction.h"

#include <functional>

Instruction::Instruction(int8 mode, int32 source, int8 destination, std::function<double*(int8, int32, int8, double*, double*, TpgParameters*)> operation)
{
    this->mode = mode;
    this->source = source;
    this->destination = destination;
    this->operation = operation;
}

Instruction::~Instruction()
{

}

bool Instruction::execute(const double* inputFeatures, double* registers, 
                          const TpgParameters& parameters)
{
    return NULL;
}

bool Instruction::mutate(const TpgParameters& parameters)
{
    return NULL;
}

std::string* Instruction::toString() const
{
    return nullptr;
}
