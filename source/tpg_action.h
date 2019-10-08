#ifndef TPG_UNIVERSAL_TPGACTION_H_
#define TPG_UNIVERSAL_TPGACTION_H_

#include <set>
#include <string>

#include "tpg_utility.h"

// Dependent class forward declarations
class Team;

/**
 *  @brief     Holds either an atomic action or Team reference to help TPG 
 *  navigate the graph.
 *  @details   The Action class contains either an atomic action or a Team
 *  object. If the Action holds an atomic action, then it will be returned
 *  when the getAction(..) method is called. If it holds a Team, it will
 *  instead provide the held Team with the feature set and ask it to begin
 *  its own bidding process. Once that Team has received an atomic action,
 *  the Action object will return it.
 *  @author    Robert Smith
 *  @author    Other
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 7, 2019.
 *  @pre       Initialize the TPGAlgorithm object, which generates a TPGLearn
    or TPGPlay objects and creates a population of Learners for producing bids.
 *  @bug       None yet marked.
 *  @todo      Implementation and full commenting required.
 *  @copyright Not Yet Decided.
 */
class Action
{
    int64 action;
    Team* team;
   
public:
    Action(int64);
    Action(Team*);
    ~Action();
    int64 getAction(std::set<Team>*, double*);
    bool isAtomicAction();
    bool equals(Action*);
    std::string toString();
};

#endif