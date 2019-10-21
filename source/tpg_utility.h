#ifndef TPG_UNIVERSAL_TPGUTILITY_H_
#define TPG_UNIVERSAL_TPGUTILITY_H_

#include <stdint.h>

#include <functional>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Required forward class declarations
class TpgParameters; 
class Team;
class Learner;
class MemoryModel;

// Typedefs to remove _t from integer types
typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

// Typedefs to remove _t from fast integer types
typedef int_fast8_t   int8_fast;
typedef int_fast16_t  int16_fast;
typedef int_fast32_t  int32_fast;
typedef int_fast64_t  int64_fast;

// Typedef for creating a random number generator using 64 bit Mersenne Twister
typedef std::mt19937_64 Random;

// Class definition for holding all the TPG Parameters. A struct would not work properly
// because the OperationFunction would make a struct self-referential. 
class TpgParameters
{
public:
    // Input Parameters
    int64 randomSeed;
    int32 teamPopulationSize;
    double teamGap;
    int64 maximumTeamSize;
    int64 maximumProgramSize;
    double probLearnerDelete;
    double probLearnerAdd;
    double probMutateAction;
    double probActionIsTeam;
    double probProgramAdd;
    double probProgramDelete;
    double probProgramSwap;
    double probProgramMutate;
    int16 learnerRegisterSize;
    int8 modeSize;
    int32 sourceSize;
    int8 destinationSize;
    int32 memoryModelSize;

    // Derived and Operational Parameters
    Random rng;
    std::uniform_real_distribution<double> distribution;
    std::vector<Team*> teamPopulation;
    std::vector<Team*> rootTeamPopulation;
    std::vector<Learner*> learnerPopulation;
    std::vector<int64> actionList;
    std::unordered_set<std::string*> labelList;
    std::queue<Team*> teamQueue;
    MemoryModel* memory;
    int64 nextTeamId;
    int64 nextLearnerId;
    int64 generation;

    // Public functions acting like variables
    double rngUniform() { return distribution(rng); };
};

#endif