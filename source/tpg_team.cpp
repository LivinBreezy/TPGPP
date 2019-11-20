#include "tpg_team.h"

#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "tpg_utility.h"
#include "tpg_action.h"
#include "tpg_learner.h"


///////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTOR
///////////////////////////////////////////////////////////////////////////////

Team::Team()
{
    this->id = 0;
    this->birthday = 0;
    this->learners = {};
    this->outcomes = {};
    this->learnerReferences = 0;
    this->fitness = 0.0;
}

/**
 *  @brief     Creates a new Team.
 *  @details   Creates a new original Team with no learners and no outcomes with
 *             an original ID and specified birthday.
 *  @param     birthday The creation generation of this Team.
 *  @param     parameters To obtain a new id.
 *  @todo      Testing.
 */
Team::Team(TpgParameters& parameters)
{
    this->id = ++parameters.nextTeamId;
    this->birthday = parameters.generation;
    this->learners = {};
    this->outcomes = {};
    this->learnerReferences = 0;
    this->fitness = 0.0;
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
    this->fitness = 0.0;
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
Team::Team(const Team& other, TpgParameters& parameters)
{
    this->id = ++parameters.nextTeamId;
    this->birthday = parameters.generation;
    this->learners = other.learners;
    this->outcomes = {};
    this->learnerReferences = 0;
    this->fitness = 0.0;
}

/**
 *  @brief      Nothing needed yet.
 *  @details    
 *  @todo       Make sure nothing is actually needed here.
 */
Team::~Team()
{
    for (Learner* lrnr : learners)
    {
        removeLearner(lrnr, true);
    }
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
    return learners;
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

double Team::calculateFitness()
{
    fitness = 0;
    for (auto pair : outcomes)
    {
        fitness += pair.second;
    }

    return this->getFitness();
}

double Team::getFitness() const
{
    return this->fitness;
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

bool Team::clearOutcomes()
{
    return true;
}

/**
 *  @brief
 *  @details
 *  @param
 *  @return
 *  @todo
 */
bool Team::addLearner(Learner* learner)
{
    // Attempt to find the position of the Learner if it
    // already exists in the Learner vector.
    auto position = std::find_if(
        learners.begin(),
        learners.end(),
        [learner](Learner* l) {return *l == *learner; }
    );
    
    // don't add if learner in learners
    if(position != learners.end())
    {
        return false;
    }
    // learner is new to this team, add it
    else
    {
        printf("TEAM_ADD1: Learner %llu Refs %u\n", learner->getId(), learner->getReferences());
        learners.push_back(learner);
        learner->increaseReferences();
        printf("\tTEAM_ADD2: Learner %llu Refs %u\n", learner->getId(), learner->getReferences());
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
bool Team::removeLearner(Learner* learner, bool force)
{
    // find the learner in learners
    auto position = std::find_if(
        learners.begin(),
        learners.end(),
        [learner](Learner* l) {return *l == *learner; }
    );

    // remove learner if in learners, and either force or not last atomic
    if(position != learners.end() && (force || getAtomicActionCount() > 1))
    {
        learners.erase(position);
        learner->decreaseReferences();
        return true;
    }
    
    // conditions not met for deletion
    return false;    
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
int64 Team::getAction(std::unordered_set<Team*>& visited, 
    const std::vector<double>& inputFeatures, 
    TpgParameters& parameters)
{
    // to ensure no re-visits of teams
    visited.emplace(this);

    spdlog::debug("GET_ACTION_TEAM: Begin = {}", inputFeatures[0]);

    // find best learner based on highest bid
    Learner* bestLearner = *learners.begin();
    double bestBid = bestLearner->bid(inputFeatures, parameters);
    double curBid;

    spdlog::debug("GET_ACTION_TEAM: Starting Bid = {}", bestBid);

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
std::string_view Team::toString() const
{
    return "Team " + this->id;
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
