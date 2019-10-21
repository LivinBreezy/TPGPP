#include "tpg_conditional.h"

#include "tpg_memory_model.h"

ConditionalInstruction::ConditionalInstruction(TpgParameters& parameters)
    : Instruction(parameters)
{
    // Do nothing else right now
}

ConditionalInstruction::ConditionalInstruction(int8 mode, int32 source, int8 destination)
    : Instruction(mode, source, destination)
{
    // Do nothing else right now
}

ConditionalInstruction::~ConditionalInstruction()
{
    // Do nothing right now
}

bool ConditionalInstruction::execute(double* inputFeatures, double* registers, const TpgParameters& parameters) const
{
    // If we are missing the inputs and/or registers, return false.
    if (inputFeatures == nullptr || registers == nullptr)
        return false;

    // Extract the destinationValue for cleaner code
    double destinationValue = registers[this->destination];
    
    // Create a variable for holding the source value
    double sourceValue = NULL;

    // Run a switch on the mode value.
    switch (mode)
    {
        // If mode is 0, we perform a Register-Register calculation.
        case 0:
            sourceValue = registers[this->source];
            break;
        // If mode is 1, we perform an Input-Register calculation.
        case 1:
            sourceValue = inputFeatures[this->source];
            break;
        // If mode is 2, we perform a Memory-Register calculation.
        case 2:
            sourceValue = parameters.memory->read(this->source);
            break;
        // If the mode is broken, return false.
        default:
            return false;
    }

    // If we have a source value and it's greater than the destination value:
    if(destinationValue < sourceValue)
    {
        // Multiply the destination value by -1 and return true
        registers[this->destination] *= -1;
        return true;
    }

    // If we reach here, we've failed somehow. Return false.
    return false;
}

bool ConditionalInstruction::mutate(TpgParameters& parameters)
{
    return NULL;
}

std::string ConditionalInstruction::getType() const
{
    return std::string("con");
}

std::string ConditionalInstruction::toString() const
{
    return this->getType() + " "
        + std::to_string(this->mode) + " "
        + std::to_string(this->source) + " "
        + std::to_string(this->destination);
}

std::string ConditionalInstruction::toStorage() const
{
    return this->toString();
}