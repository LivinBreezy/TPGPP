#ifndef TPG_UNIVERSAL_TPGLEARNER_H_
#define TPG_UNIVERSAL_TPGLEARNER_H_

#include "tpg_utility.h"

// Dependant class forward declarations
class Action;
class Program;
class Team;

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
