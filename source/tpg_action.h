#ifndef TPG_UNIVERSAL_TPGACTION_H_
#define TPG_UNIVERSAL_TPGACTION_H_

#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>

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
 *  @author    Ryan Amaral
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 23, 2019.
 *  @pre       Initialize the TPGAlgorithm object, which generates a TPGLearn
	or TPGPlay objects and creates a population of Learners for producing bids.
 *  @bug       None yet marked.
 *  @todo      Implementation and full commenting required. Perhaps add a mutate
 *             function.
 *  @copyright Not Yet Decided.
 */
class Action
{
    int64 action;
    Team* team;
   
public:
    // constructors and destructor
    Action(int64);
    Action(Team&);
    Action(const Action&);
    ~Action();

    // getters and setters
    int64 getAction(std::unordered_set<Team*>&, const double*) const;
    int64 getAtomic() const;
    Team* getTeam() const;
    bool isAtomicAction() const;

    // core functionality
    int64 getAction(std::unordered_set<Team*>&, const double*, TpgParameters& parameters) const;
    
    // utility
    bool operator==(const Action&) const;

    friend std::ofstream& operator<<(std::ofstream& out, const Action& action)
    {
        out << (action.isAtomicAction() ? 
            ("A" + std::to_string(action.action)) : ("T" + std::to_string(action.team->getId())));

        return out;
    }
    
    friend std::ifstream& operator>>(std::ifstream& in, const Action& action)
    {
        std::string input;
        in >> input;

        // atomic
        if (input.substr(0,1).compare("A"))
        {
            action.action = std::stoi(input.substr(1, input.length-1));
        }
        // team
        else
        {
            // todo: how will I get team by id? maybe add a static function to utility?   
        }

        return in;
    }
};

#endif