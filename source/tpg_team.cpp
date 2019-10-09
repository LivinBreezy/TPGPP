
#include "tpg_team.h"

#include <map>
#include <string>
#include <vector>

#include "tpg_utility.h"
#include "tpg_action.h"
#include "tpg_learner.h"

Team::Team(int64 birthday, TpgParameters* parameters)
{
    this->id = parameters->nextTeamId++;
    this->birthday = birthday;
    this->learners = {};
    this->outcomes = {};
    this->learnerReferences = 0;
}

Team::Team(int64 id, int64 birthday, std::vector<Learner> learners, std::map<std::string, double> outcomes)
{
    this->id = id;
    this->birthday = birthday;
    this->learners = learners;
    this->outcomes = outcomes;
    int32 learnerReferences = static_cast<int32>(this->learners.size());
}

Team::~Team()
{

}

bool Team::mutate(TpgParameters* parameters)
{
    return NULL;
}

int32 Team::size()
{
    return NULL;
}

int32 Team::numberOfOutcomes()
{
    return NULL;
}

int64 Team::getBirthday()
{
    return this->birthday;
}

int64 Team::getId()
{
    return this->id;
}

std::vector<Learner>* Team::getLearners()
{
    return nullptr;
}

Action* Team::getAction(double* inputFeatures)
{
    return nullptr;
}

int32 Team::getReferences()
{
    return NULL;
}

int32 Team::getAtomicActionCount()
{
    return NULL;
}

double Team::getOutcome(std::string outcomeName)
{
    return NULL;
}

bool Team::setOutcome(std::string outcomeName, double outcomeValue)
{
    return NULL;
}

bool Team::deleteOutcome(std::string outcomeName)
{
    return NULL;
}

bool Team::addLearner(Learner* learner)
{
    return NULL;
}

bool Team::removeLearner(Learner* learner)
{
    return NULL;
}

int32 Team::increaseReferences()
{
    return NULL;
}

int32 Team::decreaseReferences()
{
    return NULL;
}

int32 Team::compareTo(Team* other)
{
    return NULL;
}

std::string* Team::toString()
{
    return nullptr;
}

bool Team::operator<(const Team& rhs) const
{
    return id < rhs.id;
}

bool Team::saveToFile(Team* teamPointer, std::string* filePath, std::string* fileMode)
{
    return NULL;
}

Team* Team::loadFromFile(std::string* filePath)
{
    return nullptr;
}
