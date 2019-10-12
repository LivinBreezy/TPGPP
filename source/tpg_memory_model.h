#ifndef TPG_UNIVERSAL_TPGMEMORYMODEL_H_
#define TPG_UNIVERSAL_TPGMEMORYMODEL_H_

#include "tpg_utility.h"

#include <string>

/**
 *  @brief     Holds a matrix of memory for Learners to access.
 *  @details   The MemoryModel class contains a single matrix which represents
 *  the global memory state of a TPG learning environment. It is generated by
 *  providing the row and column dimensions of the model, or by providing an
 *  existing MemoryModel to copy from. The matrix is created and the storage
 *  probabilities are generated based on the generateProbabilities() function.
 *  Once the probabilities are created, the memory is available for reading
 *  and writing. 
 *  @author    Robert Smith
 *  @author    Ryan Amaral
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 12, 2019.
 *  @pre       Initialize the TPGAlgorithm object, which generates a TPGLearn
    or TPGPlay object.
 *  @bug       None yet marked.
 *  @todo      Implementation and full commenting required.
 *  @copyright Not Yet Decided.
 */
class MemoryModel
{
    double** memory;
    double* probabilities;

public:
    MemoryModel(int32, int32);
    MemoryModel(const double**);
    ~MemoryModel();
    double* generateProbabilities();
    double read(int32) const;
    bool write(const double*);
    std::string* toString() const;
};

#endif