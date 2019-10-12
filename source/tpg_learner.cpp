#include "tpg_learner.h"

#include "tpg_utility.h"

#include "tpg_action.h"
#include "tpg_program.h"
#include "tpg_team.h"

Learner::Learner(int64 id, int64 birthday, int64 action, int16 teamReferences, 
                  Program& program)
{
    this->id = id;
    this->birthday = birthday;
    this->action = new Action(action);
    this->teamReferences = teamReferences;
    this->program = &program;
}

Learner::Learner(int64 id, int64 birthday, Team& team, int16 teamReferences, Program& program)
{
    this->id = id;
    this->birthday = birthday;
    this->action = new Action(team);
    this->teamReferences = teamReferences;
    this->program = &program;
}

Learner::Learner(int64 birthday, int64 action, TpgParameters& parameters)
{
    this->id = parameters.nextLearnerId++;
    this->birthday = birthday;
    this->action = new Action(action);
    this->teamReferences = 0;
    this->program = new Program(parameters);
}

Learner::Learner(int64 birthday, Team& team, TpgParameters& parameters)
{
    this->id = parameters.nextLearnerId++;
    this->birthday = birthday;
    this->action = new Action(team);
    this->teamReferences = 0;
    this->program = new Program(parameters);
}

Learner::Learner(int64 birthday, const Learner& other, TpgParameters& parameters)
{
    this->id = parameters.nextLearnerId++;
    this->birthday = birthday;
    this->action = new Action(*other.getActionObject());
    this->teamReferences = other.getReferences();
    // TODO: (Robert) Set up Program to make a copy from a previous program,
    //                rather than just defaulting to something random.
    this->program = new Program(parameters);
}

Learner::~Learner()
{
    delete action;
    action = nullptr;

    delete program;
    program = nullptr;
}

/**
 *  @brief     Returns a bid value by executing the program.
 *  @details   
 *  @param     inputFeatures A double array representing the environment's
 *  complete feature set.
 *  @return    A double value representing this Learner's bid.
 *  @todo      Testing required.
 */
double Learner::bid(const double* inputFeatures)
{
    return program->execute(inputFeatures);
}

/**
 *  @brief     Returns the length of this Learner's Program (number of Instructions).
 *  @details   
 *  @return    An int representing the length of the Learner's Program.
 *  @todo      Testing required.
 */
int32 Learner::programLength() const
{
    return static_cast<int32>(program->getInstructions()->size());
}

int64 Learner::getID() const
{
    return NULL;
}

Program* Learner::getProgram() const
{
    return program;
}

Action* Learner::getActionObject() const
{
    return nullptr;
}

std::string* Learner::getActionType() const
{
    return nullptr;
}

int64 Learner::getBirthday() const
{
    return NULL;
}

int32 Learner::getReferences() const
{
    return NULL;
}

bool Learner::mutateAction(const Action&)
{
    return NULL;
}

bool Learner::mutateProgram(const TpgParameters&)
{
    return NULL;
}

bool Learner::mutate(const TpgParameters&)
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

std::string* Learner::toString() const
{
    return nullptr;
}

bool Learner::saveToFile(const Learner&, const std::string&, const std::string&)
{
    return NULL;
}

Learner* Learner::loadFromFile(const std::string&)
{
    return nullptr;
}
