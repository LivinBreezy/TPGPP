#include "tpg_write.h"

#include "tpg_memory_model.h"

bool MemWriteOperation::execute(int8 mode, int32 source, int8 destination,
    const double* inputFeatures, double* registers,
    const TpgParameters& parameters) const
{
    // If we are missing the inputs and/or registers, return false.
    if(registers == nullptr)
        return false;

    // Perform a memory write operation on the current registers
    parameters.memory->write(registers);

    // We have successfully written, so return true
    return true;
}

std::string MemWriteOperation::toString() const
{
    return std::string("write");
}

std::string MemWriteOperation::toStorage() const
{
    return this->toString();
}