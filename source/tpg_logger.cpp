
#include "tpg_logger.h"

#include <string>

#include "tpg_learner.h"
#include "tpg_team.h"

Logger::Logger()
{

}

Logger::~Logger()
{

}

bool Logger::savestate(const TpgParameters& parameters, const std::string& filePath) const
{
    return NULL;
}

bool Logger::saveTeam(const Team& team) const
{
    return NULL;
}

bool Logger::saveLearner(const Learner& learner) const
{
    return NULL;
}

bool Logger::consoleOutput(const std::string& message) const
{
    return NULL;
}