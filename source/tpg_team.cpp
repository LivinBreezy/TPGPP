
#include "tpg_team.h"

#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>
#include <set>

#include "tpg_utility.h"
#include "tpg_action.h"
#include "tpg_learner.h"

Team::Team(const int64 birthday, TpgParameters& parameters)
{
    this->id = parameters.nextTeamId++;
    this->birthday = birthday;
    this->learners = {};
    this->outcomes = {};
    this->learnerReferences = 0;
}

Team::Team(const int64 id, const int64 birthday, std::vector<Learner*> learners, std::unordered_map<std::string, double> outcomes)
{
    this->id = id;
    this->birthday = birthday;
    this->learners = learners;
    this->outcomes = outcomes;
    this->learnerReferences = 0;
}

Team::~Team()
{

}

bool Team::mutate(const TpgParameters& parameters)
{
    return NULL;
}

int32 Team::numberOfLearners() const
{
    return static_cast<int32>(learners.size());
}

int32 Team::numberOfOutcomes() const
{
    return static_cast<int32>(outcomes.size());
}

int64 Team::getBirthday() const
{
    return this->birthday;
}

int64 Team::getId() const
{
    return this->id;
}

std::vector<Learner*>& Team::getLearners()
{
    return learners;
}

int64 Team::getAction(std::set<Team*>& visited, const double* inputFeatures)
{
    // to ensure no re-visits of teams
    visited.emplace(this);

    // find best learner based on highest bid
    Learner* bestLearner = *learners.begin();
    double bestBid = bestLearner->bid(inputFeatures);
    double curBid;
    for (auto lrnrIt = learners.begin() + 1; lrnrIt != learners.end(); ++lrnrIt)
    {
        // only consider learners already visited
        if (std::find(visited.begin(), visited.end(), this) == visited.end())
        {
            // replace best learner and bid with current if higher
            curBid = (*lrnrIt)->bid(inputFeatures);
            if (curBid > bestBid) {
                bestLearner = *lrnrIt;
                bestBid = curBid;
            }
        }
    }

    // take the action of the best
    return bestLearner->getActionObject()->getAction(visited, inputFeatures);
}

int32 Team::getReferences() const
{
    return learnerReferences;
}

int32 Team::getAtomicActionCount() const
{
    int32 numAtomic = 0;
    for (auto it = learners.begin(); it != learners.end(); ++it)
    {
        if((*it)->getActionObject()->isAtomicAction())
        {
            ++numAtomic;
        }
    }

    return numAtomic;
}

double Team::getOutcome(const std::string_view outcomeName) const
{
    return outcomes.at(outcomeName.data());
}

bool Team::setOutcome(const std::string_view outcomeName, const double outcomeValue)
{
    return outcomes.insert_or_assign(outcomeName.data(), outcomeValue).second;
}

bool Team::deleteOutcome(const std::string_view outcomeName)
{
    return outcomes.erase(outcomeName.data());
}

bool Team::addLearner(Learner& learner)
{
    // don't add if learner in learners
    if (std::find(learners.begin(), learners.end(), &learner) != learners.end())
    {
        return false;
    }
    // learner is new to this team, add it
    else
    {
        learners.push_back(&learner);
        learner.increaseReferences();
        return true;
    }
}

bool Team::removeLearner(Learner& learner)
{
    // find the learner in learners
    auto lrn = std::find(learners.begin(), learners.end(), &learner);
    // remove learner if in learners
    if (lrn != learners.end()) 
    {
        learners.erase(lrn);
        (*lrn)->decreaseReferences();
        return true;
    }
    // learner not in learners
    else
    {
        return false;
    }
}

int32 Team::increaseReferences()
{
    return ++learnerReferences;
}

int32 Team::decreaseReferences()
{
    return --learnerReferences;
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

bool Team::saveToFile(const Team& teamPointer, const std::string_view filePath, const std::string_view fileMode)
{
    return NULL;
}

Team* Team::loadFromFile(const std::string_view filePath)
{
    return nullptr;
}
