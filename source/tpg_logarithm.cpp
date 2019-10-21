#include "tpg_logarithm.h"

#include "tpg_memory_model.h"

LogarithmInstruction::LogarithmInstruction(TpgParameters& parameters)
    : Instruction(parameters)
{
    // Do nothing else right now
}

LogarithmInstruction::LogarithmInstruction(int8 mode, int32 source, int8 destination)
    : Instruction(mode, source, destination)
{
    // Do nothing else right now
}

LogarithmInstruction::~LogarithmInstruction()
{
    // Do nothing right now
}

bool LogarithmInstruction::execute(double* inputFeatures, double* registers, const TpgParameters& parameters) const
{
    // If we are missing the inputs and/or registers, return false.
    if (inputFeatures == nullptr || registers == nullptr)
        return false;

    // Run a switch on the mode value.
    switch (mode)
    {
        // If mode is 0, we perform a Register-Register calculation.
    case 0:
        registers[this->destination] = log(registers[this->source]);
        return true;
        // If mode is 1, we perform an Input-Register calculation.
    case 1:
        registers[this->destination] = log(inputFeatures[this->source]);
        return true;
        // If mode is 2, we perform a Memory-Register calculation.
    case 2:
        registers[this->destination] = log(parameters.memory->read(this->source));
        return true;
    }

    // If mode is broken, we return false.
    return false;
}

bool LogarithmInstruction::mutate(TpgParameters& parameters)
{
    return NULL;
}

std::string LogarithmInstruction::getType() const
{
    return std::string("log");
}

std::string LogarithmInstruction::toString() const
{
    return this->getType() + " "
        + std::to_string(this->mode) + " "
        + std::to_string(this->source) + " "
        + std::to_string(this->destination);
}

std::string LogarithmInstruction::toStorage() const
{
    return this->toString();
}