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
 *  @author    Ryan Amaral
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 12, 2019.
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
    Learner(int64, int64, int64, int16, Program&);
    Learner(int64, int64, Team&, int16, Program&);
    Learner(int64, int64, TpgParameters&);
    Learner(int64, Team&, TpgParameters&);
    Learner(int64, const Learner&, TpgParameters&);
    ~Learner();
    double bid(const double*);
    int32 programLength() const;
    int64 getID() const;
    Program getProgram() const;
    Action* getActionObject() const;
    std::string getActionType() const;
    int64 getBirthday() const;
    int32 getReferences() const;
    bool mutateAction(const Action&);
    bool mutateProgram(const TpgParameters&);
    bool mutate(const TpgParameters&);
    int32 increaseReferences();
    int32 decreaseReferences();
    std::string toString() const;
    static bool saveToFile(const Learner&, const std::string&, const std::string&);
    static Learner* loadFromFile(const std::string&);
};

#endif