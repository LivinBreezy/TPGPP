#include "tpg_memory_model.h"

MemoryModel::MemoryModel(int32 rows, int32 columns)
{
    this->rows = rows;
    this->columns = columns;
    
    this->memory = new double*[rows];

    for(int i = 0; i < rows; ++i)
    {
        memory[i] = new double[columns];
    }

    generateProbabilities();
}

MemoryModel::MemoryModel(MemoryModel* other)
{
    this->rows = other->rows;
    this->columns = other->columns;

    this->memory = new double* [rows];

    for (int i = 0; i < rows; ++i)
    {
        memory[i] = new double[columns];

        for (int j = 0; j < columns; ++j)
        {
            memory[i][j] = other->memory[i][j];
        }
    }

    this->probabilities = new double[rows/2];

    for (int i = 0; i < rows / 2; ++i)
    {
        this->probabilities[i] = other->probabilities[i];
    }
}

MemoryModel::~MemoryModel()
{
    for (int i = 0; i < this->rows; ++i)
    {
        delete[] memory[i];
    }

    delete[] memory;
    delete[] probabilities;
}

void MemoryModel::generateProbabilities()
{
    // The probabilities are symmetrical and thus
        // we only have to generate them for half of the rows.
    probabilities = new double[rows/2];

    // Run the equation and store the result in each index.
    for (int i = 0; i < rows / 2; ++i)
    {
        probabilities[i] = 0.25 - pow((0.01 * i), 2.0);
    }
}

double MemoryModel::read(int32 inputIndex) const
{
    // Ensure the index is within range
    int index = (int)(inputIndex % (rows * columns));

    // Turn the index into a row and column.
    int row = index / columns;
    int col = index % columns;

    // Return the data stored in memory at this location.
    return memory[row][col];
}

bool MemoryModel::write(const std::vector<double>& registers, 
    TpgParameters& parameters)
{
    // If the registers aren't the same width as the columns, check your parameters!
    if (registers.size() != columns)
    {
        spdlog::error("MEMORY_MODEL: Registers do not match columns. Why?");
        exit(-50);
    }

    // We can do two rows at a time, so we only need to iterate rows/2 times.
    for (int i=0; i < (rows - 1) / 2; i++)
    {
        // Calculate the first and second row indexes.
        int row1 = (rows - 1) / 2 - i;
        int row2 = (rows - 1) / 2 + i + 1;

        // Iterate through the columns and run the probabilistic memory
        // writes across the entire register set.
        for (int col = 0; col < columns; col++)
        {
            // If our RNG is within the write probability, we
            // write the register value to the related column.
            if (parameters.rngUniform() < probabilities[i])
                memory[row1][col] = registers[col];
            if (parameters.rngUniform() < probabilities[i])
                memory[row2][col] = registers[col];
        }
    }

    return true;
}

std::string MemoryModel::toString() const
{
    return std::string("Shart");
}