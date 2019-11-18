#ifndef TPG_UNIVERSAL_TPGOPERATION_H_
#define TPG_UNIVERSAL_TPGOPERATION_H_

#include "tpg_utility.h"

/**
 *  @brief     Represents a register-based operation.
 *  @details   The Operation class represents a single register-based operation
 *  capable of being performed on a set of registers using a given input 
 *  feature set. The class contains a method for performing its designated
 *  execution on a provided state, which makes the Operation class thread-safe.
 *  @author    Robert Smith
 *  @version   v0.1 Beta
 *  @date      Created on October 22, 2019. Last updated on October 22, 2019.
 *  @pre       When Learners are initialized, they will be given a Program
 *  which generates and holds Instructions.
 *  @bug       None yet marked.
 *  @todo      Implementation and full commenting required.
 *  @copyright Not Yet Decided.
 */
class Operation
{
public:
    virtual bool execute(int8, 
        int32, 
        int8, 
        const std::vector<double>&, 
        std::vector<double>&, 
        TpgParameters&) const = 0;
    virtual std::string toString() const = 0;
    virtual std::string toStorage() const = 0;
};

#endif