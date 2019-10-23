#ifndef TPG_TESTING_TPGTEST_H_
#define TPG_TESTING_TPGTEST_H_

#include "tpg_utility.h"

#include "tpg_algorithm_mode.h"

class TpgTest: public TpgMode
{
public:
    TpgTest();
    ~TpgTest();
    std::string getType();
};

#endif