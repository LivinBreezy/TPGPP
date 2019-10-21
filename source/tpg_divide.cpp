#include "tpg_divide.h"

#include "tpg_memory_model.h"

DivideInstruction::DivideInstruction(TpgParameters& parameters)
    : Instruction(parameters)
{
    // Do nothing else right now
}

DivideInstruction::DivideInstruction(int8 mode, int32 source, int8 destination)
    : Instruction(mode, source, destination)
{
    // Do nothing else right now
}

DivideInstruction::~DivideInstruction()
{
    // Do nothing right now
}

bool DivideInstruction::execute(double* inputFeatures, double* registers, const TpgParameters& parameters) const
{
    // If we are missing the inputs and/or registers, return false.
    if (inputFeatures == nullptr || registers == nullptr)
        return false;

    // Run a switch on the mode value.
    switch (mode)
    {
        // If mode is 0, we perform a Register-Register calculation.
    case 0:
        registers[this->destination] /= registers[this->source];
        return true;
        // If mode is 1, we perform an Input-Register calculation.
    case 1:
        registers[this->destination] /= inputFeatures[this->source];
        return true;
        // If mode is 2, we perform a Memory-Register calculation.
    case 2:
        registers[this->destination] /= parameters.memory->read(this->source);
        return true;
    }

    // If mode is broken, we return false.
    return false;
}

bool DivideInstruction::mutate(TpgParameters& parameters)
{
    return NULL;
}

std::string DivideInstruction::getType() const
{
    return std::string("div");
}

std::string DivideInstruction::toString() const
{
    return this->getType() + " "
        + std::to_string(this->mode) + " "
        + std::to_string(this->source) + " "
        + std::to_string(this->destination);
}

std::string DivideInstruction::toStorage() const
{
    return this->toString();
}