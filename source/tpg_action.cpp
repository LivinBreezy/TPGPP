
#include "tpg_action.h"

Action::Action(int64 action)
{
    this->action = action;
    this->team = nullptr;
}

Action::Action(Team* team)
{
    this->action = -1;
    this->team = team;
}

Action::~Action()
{

}

int64 Action::getAction(std::set<Team>* visited, double* inputFeatures)
{
    return NULL;
}

bool Action::isAtomicAction()
{
    return NULL;
}

bool Action::equals(Action* other)
{
    return NULL;
}

std::string* Action::toString()
{
    return nullptr;
}