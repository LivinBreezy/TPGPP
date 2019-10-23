#ifndef TPG_TRAINING_TPGLEARN_H_
#define TPG_TRAINING_TPGLEARN_H_

#include "tpg_utility.h"

#include "tpg_algorithm_mode.h"

class TpgLearn: public TpgMode
{
    TpgParameters parameters;

    void mergeParameters(TpgParameters&, std::unordered_map<std::string, double>&);

public:
    TpgLearn(std::unordered_map<std::string, double>&);
    ~TpgLearn();
    bool setActions(const std::vector<int64>&);
    bool initializeEnvironment();
    bool initializePopulations();
    int64 participate(double*);
    int64 participate(double*, int64*);
    bool rewardCurrentTeam(std::string&, double& reward);
    void generateNewTeams();
    bool mutate(int64, Team&);
    void selection();
    void cleanup();
    void nextGeneration();
    void printStats();
    int32 getRemainingTeams();
    int64 getGenerations();
    std::string getType();
};

#endif