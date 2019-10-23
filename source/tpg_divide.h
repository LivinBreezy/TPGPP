#ifndef TPG_OPERATIONS_TPGDIVIDE_H_
#define TPG_OPERATIONS_TPGDIVIDE_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_operation.h"

class DivideOperation : public Operation
{
public:
    bool execute(int8, int32, int8, const double*, double*,
        const TpgParameters&) const;
    std::string toString() const;
    std::string toStorage() const;
};

#endif