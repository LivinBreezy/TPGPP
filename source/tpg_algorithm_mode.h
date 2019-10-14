#ifndef TPG_UNIVERSAL_TPGALGORITHMTYPE_H_
#define TPG_UNIVERSAL_TPGALGORITHMTYPE_H_

#include "tpg_utility.h"

#include <string>

class TpgMode
{
public:
    virtual std::string getType() = 0;
};

#endif