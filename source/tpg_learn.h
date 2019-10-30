#ifndef TPG_TRAINING_TPGLEARN_H_
#define TPG_TRAINING_TPGLEARN_H_

#include "tpg_utility.h"

#include "tpg_algorithm_mode.h"

class TpgLearn: public TpgMode
{
  public:
    TpgLearn(std::unordered_map<std::string, double>&);
    ~TpgLearn();
    bool setActions(const std::vector<int64>&);
    bool initializeEnvironment();
    bool initializePopulations();
    int64 participate(double*);
    int64 participate(double*, int64*);
    bool rewardCurrentTeam(std::string&, double& reward);
    void executeReproduction();
    void cleanup();
    int64 nextGeneration();
    void printStats();
    int32 getRemainingTeams();
    int64 getGenerations();
    std::string getType();

  private:
    TpgParameters parameters;
    void mergeParameters(TpgParameters&, std::unordered_map<std::string, double>&);
};

#endif