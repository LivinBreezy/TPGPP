
#include "tpg_memory_model.h"

MemoryModel::MemoryModel(int32 rows, int32 columns)
{
    this->memory = nullptr;
    this->probabilities = nullptr;
}

MemoryModel::MemoryModel(double** other)
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

double MemoryModel::read(int32 index)
{
    return NULL;
}

bool MemoryModel::write(double* registers)
{
    return NULL;
}

std::string* MemoryModel::toString()
{
    return nullptr;
}