/** Defines an action to be held and enacted by a learner.
 *  
 *
 *
 */

#include "tpg_action.h"

/** Create an Action initialized to the atomic action defined by action parameter.
 *
 *
 *
 */
Action::Action(int64 action)
{
    this->action = action;
    this->team = nullptr;
}

/** Create an Action initialized to the team defined by team parameter.
 *
 *
 *
 */
Action::Action(Team* team)
{
    this->action = -1;
    this->team = team;
}

/** Destruct an Action as necessary.
 *
 *
 *
 */
Action::~Action()
{

}

/** Retrieve an atomic action to be enacted on the environment.
 *
 *
 *
 */
int64 Action::getAction(std::set<Team>* visited, double* inputFeatures)
{
    return this->action;
}

/** Return true if this action holds an atomic action. Otherwise false.
 *
 *
 *
 */
bool Action::isAtomicAction()
{
    return true;
}

/** Return true if this action and the other action are considered equal.
 *
 *
 *
 */
bool Action::equals(Action* other)
{
    return true;
}

/** Return the string representation of this Action object.
 *
 *
 *
 */
std::string Action::toString()
{
    return "";
}