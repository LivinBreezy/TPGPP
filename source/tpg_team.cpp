
#include "tpg_team.h"

#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>
#include <set>

#include "tpg_utility.h"
#include "tpg_action.h"
#include "tpg_learner.h"

///////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTOR
///////////////////////////////////////////////////////////////////////////////

/**
 *  @brief     Creates a new Team.
 *  @details   Creates a new original Team with no learners and no outcomes with
 *             an original ID and specified birthday.
 *  @param     birthday The creation generation of this Team.
 *  @param     parameters To obtain a new id.
 *  @todo      Testing.
 */
Team::Team(const int64 birthday, TpgParameters& parameters)
{
    this->id = ++parameters.nextTeamId;
    this->birthday = birthday;
    this->learners = {};
    this->outcomes = {};
    this->learnerReferences = 0;
}

/**
 *  @brief      Creates a new team, using features from an existing one.
 *  @details    Creates a new team which copies the ID, birthday, learners and 
 *              outcomes provided. Used for when loading in a team from file.
 *  @param      id The unique ID of the Team.
 *  @param      birthday The creation generation of this Team.
 *  @param      learners The team's learners.
 *  @param      outcomes The outcomes of the Team.
 *  @todo       Testing. And maybe also load in learnerReferences.
 */
Team::Team(const int64 id, const int64 birthday, std::vector<Learner*> learners, std::unordered_map<std::string, double> outcomes)
{
    this->id = id;
    this->birthday = birthday;
    this->learners = learners;
    this->outcomes = outcomes;
    this->learnerReferences = 0;
}

/**
 *  @brief     Creates a new Team with the same learners as the other Team.
 *  @details   Creates a new original Team with the same learners as the other
 *             Team. Otherwise this is a brand new Team with a unique ID.
 *  @param     other The Team to take the Learners from.
 *  @param     birthday The creation generation of this Team.
 *  @param     parameters To obtain a new id.
 *  @todo      Testing.
 */
Team::Team(const Team& other, const int64 birthday, TpgParameters& parameters)
{
    this->id = ++parameters.nextTeamId;
    this->birthday = birthday;
    this->learners = other.learners;
    this->outcomes = {};
    this->learnerReferences = 0;
}

/**
 *  @brief      Nothing needed yet.
 *  @details    
 *  @todo       Make sure nothing is actually needed here.
 */
Team::~Team()
{

}

///////////////////////////////////////////////////////////////////////////////
// GETTERS AND SETTERS AND MODIFIERS
///////////////////////////////////////////////////////////////////////////////

/**
 *  @brief      Number of learners this team has.
 *  @details
 *  @param
 *  @return
 *  @todo
 */
int32 Team::numberOfLearners() const
{
    return static_cast<int32>(learners.size());
}

/**
 *  @brief      Number of outcomes this Team has.
 *  @details
 *  @param
 *  @return
 *  @todo
 */
int32 Team::numberOfOutcomes() const
{
    return static_cast<int32>(outcomes.size());
}

/**
 *  @brief      This Team's birthday.
 *  @details
 *  @param
 *  @return
 *  @todo
 */
int64 Team::getBirthday() const
{
    return this->birthday;
}

/**
 *  @brief      This Teams id.
 *  @details
 *  @param
 *  @return
 *  @todo
 */
int64 Team::getId() const
{
    return this->id;
}

/**
 *  @brief      Gets this Team's Learners.
 *  @details
 *  @param
 *  @return
 *  @todo
 */
std::vector<Learner*> Team::getLearners()
{
    return *learners;
}

/**
 *  @brief      The number of learners that reference this team as their Action.
 *  @details
 *  @param
 *  @return
 *  @todo
 */
int32 Team::getReferences() const
{
    return learnerReferences;
}

/**
 *  @brief      The number of atomic Actions this Team has.
 *  @details
 *  @param
 *  @return
 *  @todo
 */
int32 Team::getAtomicActionCount() const
{
    int32 numAtomic = 0;
    for (auto it = learners.begin(); it != learners.end(); ++it)
    {
        if ((*it)->getActionObject()->isAtomicAction())
        {
            ++numAtomic;
        }
    }

    return numAtomic;
}

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
double Team::getOutcome(const std::string_view outcomeName) const
{
    return outcomes.at(outcomeName.data());
}

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
bool Team::setOutcome(const std::string_view outcomeName, const double outcomeValue)
{
    return outcomes.insert_or_assign(outcomeName.data(), outcomeValue).second;
}

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
bool Team::deleteOutcome(const std::string_view outcomeName)
{
    return outcomes.erase(outcomeName.data());
}

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
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

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
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

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
int32 Team::increaseReferences()
{
    return ++learnerReferences;
}

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
int32 Team::decreaseReferences()
{
    return --learnerReferences;
}

///////////////////////////////////////////////////////////////////////////////
// CORE FUNCTIONALITY
///////////////////////////////////////////////////////////////////////////////

/**
 *  @brief      Decides an action to submit to the environment.
 *  @details    Chooses the learner with the highest bid's Action. If the Learner's
 *              Action is a Team, that team is searched in the same fashion for
 *              an action. If the Action is atomic, then that value is propagated
 *              upward as the action to submit to the enviornment. Tracks visited
 *              Teams to avoid a potential infinite loop.
 *  @param      visited The teams already visited in this action search.
 *  @param      inputFeatures The features from the environment to derive action
 *              from.
 *  @return     An int64 representing the action to make in the environment. This
 *              value would have some meaning in the environment.
 *  @todo       Test.
 */
int64 Team::getAction(std::set<Team*>& visited, const double* inputFeatures, TpgParameters& parameters)
{
    // to ensure no re-visits of teams
    visited.emplace(this);

    // find best learner based on highest bid
    Learner* bestLearner = *learners.begin();
    double bestBid = bestLearner->bid(inputFeatures, parameters);
    double curBid;
    for (auto lrnrIt = learners.begin() + 1; lrnrIt != learners.end(); ++lrnrIt)
    {
        // only consider learners already visited
        if (std::find(visited.begin(), visited.end(), this) == visited.end())
        {
            // replace best learner and bid with current if higher
            curBid = (*lrnrIt)->bid(inputFeatures, parameters);
            if (curBid > bestBid) {
                bestLearner = *lrnrIt;
                bestBid = curBid;
            }
        }
    }

    // take the action of the best
    return bestLearner->getActionObject()->getAction(visited, inputFeatures, parameters);
}


/// maybe add a crossover method here

/**
 *  @brief      Mutate the team
 *  @details
 *  @param      parameters Contains all necessary parameters for mutating the
 *              team.
 *  @return
 *  @todo       Testing.
 */
void Team::mutate(TpgParameters& parameters, bool addLearners)
{
    // track successfull mutation attempt
    bool changed = false;

    std::vector<Learner*> tmpLearners = learners;

    while (!changed) 
    {
        // first attempt learner deletion
        for (Learner* lrnr : tmpLearners) 
        {
            // must have at-least 2 learners
            if (learners.size() <= 2)
            {
                break;
            }

            // team needs at-least 1 atomic action
            if (getAtomicActionCount() == 1 && lrnr->getActionObject()->isAtomicAction())
            {
                continue;
            }

            // delete
            if(parameters.rngFlip(parameters.probLearnerDelete))
            {
                removeLearner(*lrnr);
                changed = true;
            }
        }

        // maybe add learners
        if (addLearners)
        {
            
        }

        // remake tmp learners to remove deleted
        tmpLearners = learners;
        // new learner to add to team (mutated from original)
        Learner* newLearner;

        // mutate learners
        for (Learner* lrnr : tmpLearners)
        {
            if(parameters.rngFlip(parameters.probLearnerMutate))
            {
                // remove the learner from the team, then later add the mutated version
                removeLearner(*lrnr);

                // copy and mutate the learner
                newLearner = new Learner(parameters.generation, *lrnr, parameters);
                newLearner->mutate(parameters);

                addLearner(*newLearner);

                changed = true;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// UTILITY
///////////////////////////////////////////////////////////////////////////////

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
int32 Team::compareTo(const Team& other) const
{
    return NULL;
}

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
std::string* Team::toString() const
{
    return nullptr;
}

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
bool Team::operator<(const Team& rhs) const
{
    return id < rhs.id;
}

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
bool Team::saveToFile(const Team& teamPointer, const std::string_view filePath, const std::string_view fileMode)
{
    return NULL;
}

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
Team* Team::loadFromFile(const std::string_view filePath)
{
    return nullptr;
}
