#ifndef TPG_OPERATIONS_TPGCOSINE_H_
#define TPG_OPERATIONS_TPGCOSINE_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_operation.h"

class CosineOperation : public Operation
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