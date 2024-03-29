#ifndef TPG_UNIVERSAL_TPGLEARNER_H_
#define TPG_UNIVERSAL_TPGLEARNER_H_

#include <fstream>
#include <iostream>

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
 *  @date      Created on October 7, 2019. Last updated on October 24, 2019.
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
    int32 teamReferences;

    Action* action;
    Program* program;

public:
    // constructors and destructor
    Learner(int64, int64, int64, int16, Program&);
    Learner(int64, int64, Team&, int16, Program&);
    Learner(int64 TpgParameters&);
    Learner(Team&, TpgParameters&);
    Learner(const Learner&, TpgParameters&);
    ~Learner();

    // getters and setters
    Program getProgram(TpgParameters&) const;
    int32 programLength() const;
    int64 getID() const;
    Action* getActionObject() const;
    double bid(const std::vector<double>&);
    int32 programLength() const;
    int64 getID() const;
    Program getProgram() const;
    Action* getActionObject() const;
    std::string getActionType() const;

    int64 getBirthday() const;
    int32 getReferences() const;
    int32 increaseReferences();
    int32 decreaseReferences();

    // core functionality
    double bid(const double*, TpgParameters&);

    // utility
    friend std::ofstream& operator<<(std::ofstream& out, const Learner& learner)
    {
        out << learner.id << "\n" << 
               learner.birthday << "\n" << 
               learner.teamReferences << "\n" <<
               learner.action << "\n" <<
               learner.program;

        return out;
    }
    
    friend std::ifstream& operator>>(std::ifstream& in, const Learner& learner)
    {
        in >> learner.id >> learner.birthday >> learner.teamReferences >> 
              learner.action >> learner.program;

        return in;
    }

    std::string toString() const;
    static bool saveToFile(const Learner&, const std::string&, const std::string&);
    static Learner* loadFromFile(const std::string&);
    bool operator==(const Learner& other) { return this->id == other.id; };
};

#endif