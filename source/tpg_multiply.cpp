#include "tpg_multiply.h"

#include "tpg_memory_model.h"

MultiplyInstruction::MultiplyInstruction(TpgParameters& parameters)
    : Instruction(parameters)
{
    // Do nothing else right now
}

MultiplyInstruction::MultiplyInstruction(int8 mode, int32 source, int8 destination)
    : Instruction(mode, source, destination)
{
    // Do nothing else right now
}

MultiplyInstruction::~MultiplyInstruction()
{
    // Do nothing right now
}

bool MultiplyInstruction::execute(double* inputFeatures, double* registers, const TpgParameters& parameters) const
{
    // If we are missing the inputs and/or registers, return false.
    if (inputFeatures == nullptr || registers == nullptr)
        return false;

    // Run a switch on the mode value.
    switch (mode)
    {
        // If mode is 0, we perform a Register-Register calculation.
    case 0:
        registers[this->destination] *= registers[this->source];
        return true;
        // If mode is 1, we perform an Input-Register calculation.
    case 1:
        registers[this->destination] *= inputFeatures[this->source];
        return true;
        // If mode is 2, we perform a Memory-Register calculation.
    case 2:
        registers[this->destination] *= parameters.memory->read(this->source);
        return true;
    }

    // If mode is broken, we return false.
    return false;
}

bool MultiplyInstruction::mutate(TpgParameters& parameters)
{
    return NULL;
}

std::string MultiplyInstruction::getType() const
{
    return std::string("mul");
}

std::string MultiplyInstruction::toString() const
{
    return this->getType() + " "
        + std::to_string(this->mode) + " "
        + std::to_string(this->source) + " "
        + std::to_string(this->destination);
}

std::string MultiplyInstruction::toStorage() const
{
    return this->toString();
}