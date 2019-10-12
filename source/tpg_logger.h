#ifndef TPG_UNIVERSAL_TPGLOGGER_H_
#define TPG_UNIVERSAL_TPGLOGGER_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_learner.h"
#include "tpg_team.h"

/**
 *  @brief     Provides the TPG algorithm with logging and console output.
 *  @details   The Logger object has several methods for creating algorithm
 *  saved states, storing individual Team and Learner objects, as well as the
 *  ability to print output to the screen. By using the Logger to print output,
 *  we standardize our output and also provide extendability if we want to also
 *  log those outputs in the future.
 *  @author    Robert Smith
 *  @author    Ryan Amaral
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 12, 2019.
 *  @pre       Initialize the TPGAlgorithm object.
 *  @bug       None yet marked.
 *  @todo      Implementation and full commenting required.
 *  @copyright Not Yet Decided.
 */
class Logger
{

public:
    Logger();
    ~Logger();
    bool savestate(const TpgParameters&, const std::string&) const;
    bool saveTeam(const Team&) const;
    bool saveLearner(const Learner&) const;
    bool consoleOutput(const std::string&) const;
};

#endif