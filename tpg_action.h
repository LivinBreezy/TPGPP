#ifndef TPG_UNIVERSAL_TPGACTION_H_
#define TPG_UNIVERSAL_TPGACTION_H_

#include <set>
#include <string>

#include "tpg_utility.h"

// Dependent class forward declarations
class Team;

/** An Action holds either an atomic action or Team reference to help TPG navigate the graph. 
 * 
 *
 *
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