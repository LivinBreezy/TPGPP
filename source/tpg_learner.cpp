#include "tpg_learner.h"

#include "tpg_utility.h"

#include "tpg_action.h"
#include "tpg_program.h"
#include "tpg_team.h"

Learner::Learner(int64 id, int64 birthday, int64 action, int16 teamReferences, Program* program)
{
    this->id = id;
    this->birthday = birthday;
    this->action = new Action(action);
    this->teamReferences = teamReferences;
    this->program = program;
}

Learner::Learner(int64 id, int64 birthday, Team* team, int16 teamReferences, Program* program)
{
    this->id = id;
    this->birthday = birthday;
    this->action = new Action(team);
    this->teamReferences = teamReferences;
    this->program = program;
}

Learner::Learner(int64 birthday, int64 action, TpgParameters* parameters)
{
    this->id = parameters->nextLearnerId++;
    this->birthday = birthday;
    this->action = new Action(action);
    this->teamReferences = 0;
    this->program = new Program(parameters);
}

Learner::Learner(int64 birthday, Team* team, TpgParameters* parameters)
{
    this->id = parameters->nextLearnerId++;
    this->birthday = birthday;
    this->action = new Action(team);
    this->teamReferences = 0;
    this->program = new Program(parameters);
}

Learner::Learner(int64 birthday, Learner* other, TpgParameters* parameters)
{
    this->id = parameters->nextLearnerId++;
    this->birthday = birthday;
    this->action = other->getActionObject();
    this->teamReferences = other->getReferences();
    // TODO: (Robert) Set up Program to make a copy from a previous program,
    //                rather than just defaulting to something random.
    this->program = new Program(parameters);
}

Learner::~Learner()
{

}

/**
 *  @brief     Returns a bid value by executing the program.
 *  @details   
 *  @param     inputFeatures A double array representing the environment's
 *  complete feature set.
 *  @return    A double value representing this Learner's bid.
 *  @todo      Testing required.
 */
int64 Learner::bid(double* inputFeatures)
{
	return program->execute(inputFeatures);
}

/**
 *  @brief     Returns the length of this Learner's Program (number of Instructions).
 *  @details   
 *  @return    An int representing the length of the Learner's Program.
 *  @todo      Testing required.
 */
int32 Learner::programLength()
{
    return program->getProgramLength();
}

int64 Learner::getID()
{
    return NULL;
}

Action* Learner::getActionObject()
{
    return nullptr;
}

std::string* Learner::getActionType()
{
    return nullptr;
}

int64 Learner::getBirthday()
{
    return NULL;
}

int32 Learner::getReferences()
{
    return NULL;
}

bool Learner::mutateAction(Action*)
{
    return NULL;
}

bool Learner::mutateProgram(TpgParameters*)
{
    return NULL;
}

bool Learner::mutate(TpgParameters*)
{
    return NULL;
}

int32 Learner::increaseReferences()
{
    return NULL;
}

int32 Learner::decreaseReferences()
{
    return NULL;
}

std::string* Learner::toString()
{
    return nullptr;
}

bool Learner::saveToFile(Learner*, std::string*, std::string*)
{
    return NULL;
}

Learner* Learner::loadFromFile(std::string*)
{
    return nullptr;
}
