#include "tpg_divide.h"

#include "tpg_memory_model.h"

bool DivideOperation::execute(int8 mode, int32 source, int8 destination,
    const std::vector<double>& inputFeatures, std::vector<double>& registers,
    TpgParameters& parameters) const
{
    // Run a switch on the mode value.
    switch(mode)
    {
        // If mode is 0, we perform a Register-Register calculation.
        case 0:
            registers[destination] = registers[source % registers.size()] / 2.0;
            return true;
        // If mode is 1, we perform an Input-Register calculation.
        case 1:
            registers[destination] = inputFeatures[source % inputFeatures.size()] / 2.0;
            return true;
        // If mode is 2, we perform a Memory-Register calculation.
        case 2:
            registers[destination] = parameters.memory->read(source) / 2.0;
            return true;
    }

    // If mode is broken, we return false.
    return false;
}

std::string DivideOperation::toString() const
{
    return std::string("div");
}

std::string DivideOperation::toStorage() const
{
    return this->toString();
}