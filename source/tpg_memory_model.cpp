
#include "tpg_memory_model.h"

MemoryModel::MemoryModel(int32 rows, int32 columns)
{
    this->memory = nullptr;
    this->probabilities = nullptr;
}

MemoryModel::MemoryModel(const double** other)
{
    this->memory = nullptr;
    this->probabilities = nullptr;
}

MemoryModel::~MemoryModel()
{

}

double* MemoryModel::generateProbabilities()
{
    return nullptr;
}

double MemoryModel::read(int32 index) const
{
    return NULL;
}

bool MemoryModel::write(const double* registers)
{
    return NULL;
}

std::string* MemoryModel::toString() const
{
    return nullptr;
}