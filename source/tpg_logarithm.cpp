#include "tpg_logarithm.h"

#include "tpg_memory_model.h"

bool LogarithmOperation::execute(int8 mode, int32 source, int8 destination,
    const double* inputFeatures, double* registers,
    const TpgParameters& parameters) const
{
    // If we are missing the inputs and/or registers, return false.
    if (inputFeatures == nullptr || registers == nullptr)
        return false;

    // Run a switch on the mode value.
    switch (mode)
    {
        // If mode is 0, we perform a Register-Register calculation.
    case 0:
        registers[destination] = log(registers[source]);
        return true;
        // If mode is 1, we perform an Input-Register calculation.
    case 1:
        registers[destination] = log(inputFeatures[source]);
        return true;
        // If mode is 2, we perform a Memory-Register calculation.
    case 2:
        registers[destination] = log(parameters.memory->read(source));
        return true;
    }

    // If mode is broken, we return false.
    return false;
}

std::string LogarithmOperation::toString() const
{
    return std::string("log");
}

std::string LogarithmOperation::toStorage() const
{
    return this->toString();
}