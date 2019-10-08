#ifndef TPG_UNIVERSAL_TPGLEARNER_H_
#define TPG_UNIVERSAL_TPGLEARNER_H_

#include "tpg_utility.h"

// Dependant class forward declarations
class Action;
class Program;
class Team;

/**
 *  @brief     Holds a Program and an Action, using both to act on environment.
 *  @details   The Learner class contains a Program and an Action. When a
 *  Learner receives a feature set, it evaluates the feature set using its 
 *  stored Program. The Program produces a bid, which the Learner's host team
 *  compares against all other Learners under its control. The Learner with the
 *  highest bid will then return its Action to the Team, which will be enacted
 *  on the environment.
 *  @author    Robert Smith
 *  @author    Other
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 7, 2019.
 *  @pre       Initialize the TPGAlgorithm object, which generates a TPGLearn
    or TPGPlay objects.
 *  @bug       None yet marked.
 *  @todo      Implementation and full commenting required.
 *  @copyright Not Yet Decided.
 */
class Learner
{
    int64 id;
    int64 birthday;
    Action* action;
    int32 teamReferences;
    Program* program;

public:
    Learner(int64, int64, int64, int16, Program*);
    Learner(int64, int64, Team*, int16, Program*);
    Learner(int64, int64, TpgParameters*);
    Learner(int64, Team*, TpgParameters*);
    Learner(int64, Learner*, TpgParameters*);
    int64 bid(double*);
    int32 programLength();
    int64 getID();
    Action* getActionObject();
    std::string* getActionType();
    int64 getBirthday();
    int32 getReferences();
    bool mutateAction(Action*);
    bool mutateProgram(TpgParameters*);
    bool mutate(TpgParameters*);
    int32 increaseReferences();
    int32 decreaseReferences();
    std::string* toString();
    static bool saveToFile(Learner*, std::string*, std::string*);
    static Learner* loadFromFile(std::string*);
};

#endif
