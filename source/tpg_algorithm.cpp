#include "tpg_algorithm.h"

#include <stdio.h>

#include "tpg_utility.h"
#include "tpg_learn.h"
#include "tpg_test.h"


TpgAlgorithm::TpgAlgorithm(std::string*, std::string*)
{
    this->arguments = nullptr;
    this->rng = nullptr;
    this->tpgLearn = nullptr;
    this->tpgTest = nullptr;
}

TpgAlgorithm::~TpgAlgorithm()
{

}

void TpgAlgorithm::startLearning(std::string*)
{
    return;
}

void TpgAlgorithm::startTesting(std::string*)
{
    return;
}

TpgLearn* TpgAlgorithm::getTpgLearn()
{
    return nullptr;
}

TpgTest* TpgAlgorithm::getTpgTest()
{
    return nullptr;
}

std::map<std::string, std::string>* TpgAlgorithm::readArgumentsToMap(std::string*)
{
    return nullptr;
}

///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                           MAIN FUNCTION                               //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
int main()
{
    printf("Main Function Called\n");

    return 0;
}