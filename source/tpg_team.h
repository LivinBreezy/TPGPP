#ifndef TPG_UNIVERSAL_TPGTEAM_H_
#define TPG_UNIVERSAL_TPGTEAM_H_

#include "tpg_utility.h"

#include <map>
#include <string>
#include <vector>
#include <set>

#include "tpg_learner.h"

// Dependent class forward declarations
class Action;

/**
 *  @brief     A class which represents a collective of Learner objects.
 *  @details   The Team class contains a list of Learner objects which accept 
 *  values representing an environment and use them to calculate bids. The 
 *  Learner which wins the bidding process by generating the highest bid is 
 *  considered the most sure of their success and their assigned Action is 
 *  enforced on the environment.
 *  @author    Robert Smith
 *  @author    Ryan Amaral
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 12, 2019.
 *  @pre       Initialize the TPGAlgorithm object, which generates a TPGLearn 
    or TPGPlay objects and creates a population of Teams for producing bids.
 *  @bug       None yet marked.
 *  @todo      Implementation and full commenting required. 
 *  @copyright Not Yet Decided.
 */
class Team
{
    int64 id;
    int64 birthday;
    std::vector<Learner> learners;
    std::map<std::string, double> outcomes;
    int32 learnerReferences;

public:
    Team(int64, TpgParameters&);
    Team(int64, int64, std::vector<Learner>, std::map<std::string, double>);
    ~Team();
    bool mutate(const TpgParameters&);
    int32 size() const;
    int32 numberOfOutcomes() const;
    int64 getBirthday() const;
    int64 getId() const;
    std::vector<Learner>* getLearners() const;
    int64 getAction(std::set<Team>&, const double*);
    int32 getReferences() const;
    int32 getAtomicActionCount() const;
    double getOutcome(std::string) const;
    bool setOutcome(std::string, double);
    bool deleteOutcome(std::string);
    bool addLearner(Learner&);
    bool removeLearner(Learner&);
    int32 increaseReferences();
    int32 decreaseReferences();
    int32 compareTo(const Team&) const;
    std::string* toString() const;
    bool operator<(const Team& rhs) const;
    static bool saveToFile(const Team&, const std::string&, const std::string&);
    static Team* loadFromFile(const std::string&);
};

#endif