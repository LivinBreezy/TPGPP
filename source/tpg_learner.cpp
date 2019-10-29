#include "tpg_learner.h"

#include "tpg_utility.h"

#include "tpg_action.h"
#include "tpg_program.h"
#include "tpg_team.h"

///////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTOR
///////////////////////////////////////////////////////////////////////////////

Learner::Learner(int64 id, int64 birthday, int64 action, int16 teamReferences, 
                  Program& program)
{
    this->id = id;
    this->birthday = birthday;
    this->action = new Action(action);
    this->teamReferences = teamReferences;
    this->program = &program;
}

Learner::Learner(int64 id, int64 birthday, Team& team, int16 teamReferences, 
    Program& program)
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
    //this->teamReferences = other.getReferences(); todo: this should be gone right?
    this->program = new Program(*other.program, parameters);
}

Learner::~Learner()
{
    delete action;
    action = nullptr;

    delete program;
    program = nullptr;
}

///////////////////////////////////////////////////////////////////////////////
// GETTERS AND SETTERS
///////////////////////////////////////////////////////////////////////////////

/**
 *  @brief     Returns the length of this Learner's Program (number of Instructions).
 *  @details   
 *  @return    An int representing the length of the Learner's Program.
 *  @todo      Testing required.
 */
int32 Learner::programLength() const
{
    return static_cast<int32>(program->getInstructions().size());
}

int64 Learner::getID() const
{
    return id;
}

Program Learner::getProgram(TpgParameters& parameters) const
{
    return Program(*program, parameters);
}

Action* Learner::getActionObject() const
{
    return action;
}

int64 Learner::getBirthday() const
{
    return birthday;
}

int32 Learner::getReferences() const
{
    return teamReferences;
}

int32 Learner::increaseReferences()
{
    return ++teamReferences;
}

int32 Learner::decreaseReferences()
{
    return --teamReferences;
}

///////////////////////////////////////////////////////////////////////////////
// CORE FUNCTIONALITY
///////////////////////////////////////////////////////////////////////////////

/**
 *  @brief     Returns a bid value by executing the program.
 *  @details   
 *  @param     inputFeatures A double array representing the environment's
 *  complete feature set.
 *  @return    A double value representing this Learner's bid.
 *  @todo      Testing required.
 */
double Learner::bid(const double* inputFeatures, TpgParameters& parameters)
{
    return program->execute(inputFeatures, parameters);
}

/**
 *  @brief     
 *  @details   
 *  @param     
 *  @todo      Testing required.
 */
void Learner::mutate(TpgParameters& parameters)
{
    // attempt mutation until successfull
    bool changed = false;
    while (!changed) 
    {
        // first try to mutate program
        changed = program->mutate(parameters);

        // maybe try to mutate action
        if (parameters.rngFlip(parameters.probMutateAction)) {
            changed = action->mutate(parameters);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// UTILITY
///////////////////////////////////////////////////////////////////////////////

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
