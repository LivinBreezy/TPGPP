#include "tpg_conditional.h"

#include "tpg_memory_model.h"

bool ConditionalOperation::execute(int8 mode, int32 source, int8 destination,
    const std::vector<double>& inputFeatures, std::vector<double>& registers,
    TpgParameters& parameters) const
{
    // Extract the destinationValue for cleaner code
    double destinationValue = registers[destination];
    
    // Create a variable for holding the source value
    double sourceValue = NULL;

    // Run a switch on the mode value.
    switch (mode)
    {
        // If mode is 0, we perform a Register-Register calculation.
        case 0:
            sourceValue = registers[source % registers.size()];
            break;
        // If mode is 1, we perform an Input-Register calculation.
        case 1:
            sourceValue = inputFeatures[source % inputFeatures.size()];
            break;
        // If mode is 2, we perform a Memory-Register calculation.
        case 2:
            sourceValue = parameters.memory->read(source);
            break;
        // If the mode is broken, return false.
        default:
            return false;
    }

    // If we have a source value and it's greater than the destination value:
    if(destinationValue < sourceValue)
    {
        // Multiply the destination value by -1 and return true
        registers[destination] *= -1;
        return true;
    }

    // If we reach here, we've failed somehow. Return false.
    return false;
}

std::string ConditionalOperation::toString() const
{
    return std::string("cond");
}

std::string ConditionalOperation::toStorage() const
{
    return this->toString();
}