#ifndef TPG_UNIVERSAL_TPGUTILITY_H_
#define TPG_UNIVERSAL_TPGUTILITY_H_

#include <stdint.h>

#include <functional>
#include <queue>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>

#include <boost/serialization/split_member.hpp>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

// Required forward class declarations
class TpgParameters; 
class Team;
class Learner;
class MemoryModel;
class Reproduction;

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

// Create an enumeration class for the operation types
enum class Operations { 
    Add,
    Subtract,
    Multiply,
    Divide,
    Cosine,
    Exp,
    Logarithm,
    Conditional,
    MemWrite
};

// Class definition for holding all the TPG Parameters. A struct would not work properly
// because the OperationFunction would make a struct self-referential. 
class TpgParameters
{
    friend class boost::serialization::access;

    template<class Archive>
    void save(Archive& ar, const unsigned int version)
    {

    }

    template<class Archive>
    void load(Archive& ar, const unsigned int version)
    {

    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

public:
    // Input Parameters
    int64 randomSeed;
    int32 teamPopulationSize;
    double teamGap;
    int64 maximumTeamSize;
    int64 minimumTeamSize;
    int64 minimumRootTeams;
    int64 maximumProgramSize;
    int8 numberOfOperations;
    double probLearnerDelete;
    double probLearnerAdd;
    double probLearnerMutate;
    double probMutateAction;
    double probActionIsTeam;
    double probInstructionAdd;
    double probInstructionDelete;
    double probInstructionSwap;
    double probInstructionMutate;
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
    std::unordered_set<std::string> labelList;
    std::queue<Team*> teamQueue;
    MemoryModel* memory;
    Reproduction* reproduction;
    int64 nextTeamId;
    int64 nextLearnerId;
    int64 generation;

    // Public functions acting like variables
    double rngUniform() { return distribution(rng); };

    bool rngFlip(double prob) { return rngUniform() < prob; };

    int64 rngInt64(const int64 min, const int64 max)
        {return min + static_cast<int64>(floor(rngUniform() * (max - min)));};
    
    int32 rngInt32(const int64 min, const int64 max)
        {return static_cast<int32>(rngInt64(min, max));};

    int16 rngInt16(const int64 min, const int64 max)
        {return static_cast<int16>(rngInt64(min, max));};

    int8 rngInt8(const int64 min, const int64 max)
        {return static_cast<int8>(rngInt64(min, max));};
};

#endif