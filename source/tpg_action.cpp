
#include "tpg_action.h"

#include "tpg_team.h"

///////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTOR
///////////////////////////////////////////////////////////////////////////////

Action::Action(int64 action)
{
    this->action = action;
    this->team = nullptr;
}

Action::Action(Team& team)
{
    this->action = -1;
    this->team = &team;
}

Action::Action(const Action& other)
{
    if (other.isAtomicAction()) 
    {
        this->action = other.action;
        this->team = nullptr;
    }
    else
    {
        this->action = -1;
        this->team = other.team;
    }
}

Action::~Action()
{

}

///////////////////////////////////////////////////////////////////////////////
// GETTERS AND SETTERS
///////////////////////////////////////////////////////////////////////////////

int64 Action::getAtomic() const
{
    return action;
}

Team* Action::getTeam() const
{
    return team;
}

/**
 *  @brief     Returns whether the action is atomic (int) or not (team).
 *  @details   Decides based on the value of the team variable whether the
 *             action is atomic or not. If team == nullptr then it returns true.
 *  @return    A boolean representing whether the action is atomic.
 *  @todo      Testing required.
 */
bool Action::isAtomicAction() const
{
    return action >= 0;
    //return !team;
}

///////////////////////////////////////////////////////////////////////////////
// CORE FUNCTIONALITY
///////////////////////////////////////////////////////////////////////////////

/**
 *  @brief     Get the action residing in this Action object. From the team or
 *             the atomic action if applicable.
 *  @details   If this team has its action field defined, that value will be 
 *			   returned. Otherwise the team is defined, so the action will be
 *             obtained from that team.
 *  @param     visited The set of teams already visited. To be passed on to the 
 *             team to avoid revisiting teams in action selection.
 *  @param     inputFeatures The features that the program is ran on, from the
 *             environment.
 *  @return    An int action from either the team in this Action, or the atomic
 *             action.
 *  @todo      Testing required.
 */
int64 Action::getAction(std::unordered_set<Team*>& visited, 
    const std::vector<double>& inputFeatures, 
    TpgParameters& parameters) const
{
    // just return atomic action if applicable
    if (isAtomicAction())
    {
        return action;
    }
    // delegate action selection to the team
    else
    {
        return team->getAction(visited, inputFeatures, parameters);
    }
}

///////////////////////////////////////////////////////////////////////////////
// UTILITY
///////////////////////////////////////////////////////////////////////////////

/**
 *  @brief     Returns whether this and the other action are equal.
 *  @details   If the actions are both ints, then are determined to be equal if
 *             if their values are equal. Likewise for if both actions are
 *             teams, except we compare memory addresses to see if they are the
 *             same object. If one action is of type int and the other is of
 *             type team, then they are not equal.
 *  @param     other The other action object to comare this to.
 *  @return    A boolean representing whether the actions are equivalent.
 *  @todo      Testing required.
 */
bool Action::operator==(const Action& other) const
{
    // different action types, return false
    if ((other.team && !this->team) || (!other.team && this->team)) 
    {
        return false;
    }
    // both are teams, compare team address
    else if (team) 
    {
        return other.team == this->team;
    }
    // both are ints, compare values
    else 
    {
        return other.action == this->action;
    }
}