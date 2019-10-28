#ifndef TPG_UNIVERSAL_TPGTEAM_H_
#define TPG_UNIVERSAL_TPGTEAM_H_

#include "tpg_utility.h"

#include <unordered_map>
#include <string>
#include <string_view>
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
 *  @date      Created on October 7, 2019. Last updated on October 23, 2019.
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
    int32 learnerReferences;

    std::vector<Learner*> learners;
    std::unordered_map<std::string, double> outcomes;

public:
    // constructors and destructor
    Team(const int64, TpgParameters&);
    Team(const int64, const int64, std::vector<Learner*>, 
        std::unordered_map<std::string, double>);
    Team(const Team&, const int64 birthday, TpgParameters&);
    ~Team();

    // getters and setters and modifiers
    int64 getId() const;
    int64 getBirthday() const;
    int32 numberOfLearners() const;
    int32 numberOfOutcomes() const;
    int32 getReferences() const;
    int32 increaseReferences();
    int32 decreaseReferences();
    int32 getAtomicActionCount() const;
    std::vector<Learner*> getLearners();
    double getOutcome(const std::string_view) const;
    bool setOutcome(const std::string_view, const double);
    bool deleteOutcome(const std::string_view);
    bool addLearner(Learner&);
    bool removeLearner(Learner&);


    // core functionality
    int64 getAction(std::set<Team*>&, const double*, TpgParameters&);
    void mutate(TpgParameters&, bool);


    // utility
    int32 compareTo(const Team&) const;
    std::string* toString() const;
    bool operator<(const Team& rhs) const;
    static bool saveToFile(const Team&, const std::string_view, const std::string_view);
    static Team* loadFromFile(const std::string_view);
};

#endif