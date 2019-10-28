#include "tpg_memory_model.h"

MemoryModel::MemoryModel(int32 rows, int32 columns)
{
    this->rows = rows;
    this->columns = columns;
    
    this->memory = new double*[rows];

    for(int i = 0; i < rows; i++)
    {
        memory[i] = new double[columns];
    }

    this->probabilities = new double[rows/2];
}

MemoryModel::MemoryModel(MemoryModel* other)
{
    this->rows = 0;
    this->columns = 0;

    this->memory = nullptr;
    this->probabilities = nullptr;
}

MemoryModel::~MemoryModel()
{
    for (int i = 0; i < this->rows; i++)
    {
        delete[] memory[i];
    }

    delete[] memory;
    delete[] probabilities;
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

std::string MemoryModel::toString() const
{
    return std::string("Shart");
}