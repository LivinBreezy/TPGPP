
#include "tpg_team.h"

#include <map>
#include <string>
#include <vector>

#include "tpg_utility.h"
#include "tpg_action.h"
#include "tpg_learner.h"

Team::Team(int64 birthday, TpgParameters& parameters)
{
    this->id = parameters.nextTeamId++;
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

bool Team::mutate(const TpgParameters& parameters)
{
    return NULL;
}

int32 Team::size() const
{
    return NULL;
}

int32 Team::numberOfOutcomes() const
{
    return NULL;
}

int64 Team::getBirthday() const
{
    return this->birthday;
}

int64 Team::getId() const
{
    return this->id;
}

std::vector<Learner>* Team::getLearners() const
{
    return nullptr;
}

int64 Team::getAction(std::set<Team>& visited, const double* inputFeatures)
{
    return NULL;
}

int32 Team::getReferences() const
{
    return NULL;
}

int32 Team::getAtomicActionCount() const
{
    return NULL;
}

double Team::getOutcome(std::string outcomeName) const
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

bool Team::addLearner(Learner& learner)
{
    return NULL;
}

bool Team::removeLearner(Learner& learner)
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

int32 Team::compareTo(const Team& other) const
{
    return NULL;
}

std::string* Team::toString() const
{
    return nullptr;
}

bool Team::operator<(const Team& rhs) const
{
    return id < rhs.id;
}

bool Team::saveToFile(const Team& teamPointer, const std::string& filePath, const std::string& fileMode)
{
    return NULL;
}

Team* Team::loadFromFile(const std::string& filePath)
{
    return nullptr;
}
