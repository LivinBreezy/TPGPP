#ifndef TPG_OPERATIONS_TPGEXP_H_
#define TPG_OPERATIONS_TPGEXP_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_operation.h"

class ExpOperation : public Operation
{
public:
    bool execute(int8, 
        int32, 
        int8, 
        const std::vector<double>&, 
        std::vector<double>&,
        TpgParameters&) const;
    std::string toString() const;
    std::string toStorage() const;
};

#endif