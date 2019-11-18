#include "tpg_write.h"

#include "tpg_memory_model.h"

bool MemWriteOperation::execute(int8 mode, int32 source, int8 destination,
    const std::vector<double>& inputFeatures, std::vector<double>& registers,
    TpgParameters& parameters) const
{
    // Perform a memory write operation on the current registers
    parameters.memory->write(registers, parameters);

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