
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

bool Logger::savestate(TpgParameters* parameters, std::string* filePath)
{
    return NULL;
}

bool Logger::saveTeam(Team* team)
{
    return NULL;
}

bool Logger::saveLearner(Learner* learner)
{
    return NULL;
}

bool Logger::consoleOutput(std::string* message)
{
    return NULL;
}