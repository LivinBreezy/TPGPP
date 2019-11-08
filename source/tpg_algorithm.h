#ifndef TPG_UNIVERSAL_TPGALGORITHM_H_
#define TPG_UNIVERSAL_TPGALGORITHM_H_

#include "tpg_utility.h"

#include <random>
#include <string>
#include <unordered_map>

#include "tpg_algorithm_mode.h"

// Required forward class declarations
class TpgMode;

/**
 *  @brief     The main class for the TPG learning process.
 *  @details   The TpgAlgorithm class begins by accepting a file path to a
 *  parameters file and a label for the type of algorithm to run. Once it
 *  knows whether to start a learning process or testing process, it reads
 *  in the parameters file and stores it in a map, then creates either a
 *  TpgLearn or TpgPlay object and provides parameters so they can process.
 *  @author    Robert Smith
 *  @author    Other
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 7, 2019.
 *  @pre       None. This is the first class to execute.
 *  @bug       None yet marked.
 *  @todo      Implementation and full commenting required.
 *  @copyright Not Yet Decided.
 */
class TpgAlgorithm
{
    std::unordered_map<std::string, double> arguments;
    TpgMode* tpgMode;

public:
    TpgAlgorithm(const char*, const char*);
    ~TpgAlgorithm();
    TpgMode* getTpgEntity();
    std::unordered_map<std::string, double> readArgumentsToMap(const char*);
};

#endif