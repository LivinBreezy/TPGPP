#include "tpg_add.h"

#include "tpg_memory_model.h"

/**
 * @todo Consider adding return codes for more meaningful error trace.
 */

bool AddOperation::execute(int8 mode, int32 source, int8 destination, 
        const double* inputFeatures, double* registers, 
        const TpgParameters& parameters) const
{
    // If we are missing the inputs and/or registers, return false.
    if(registers == nullptr)
        return false;
    
    // Run a switch on the mode value.
    switch (mode)
    {
        // If mode is 0, we perform a Register-Register calculation.
        case 0:
            registers[destination] += registers[source];
            return true;
        // If mode is 1, we perform an Input-Register calculation.
        case 1:
            registers[destination] += inputFeatures[source];
            return true;
        // If mode is 2, we perform a Memory-Register calculation.
        case 2:
            registers[destination] += parameters.memory->read(source);
            return true;
    }
    
    // The mode value must be wrong. We return false.
    return false;
}

std::string AddOperation::toString() const
{
    return std::string("add");
}

std::string AddOperation::toStorage() const
{
    return this->toString();
}