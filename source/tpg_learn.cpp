
#include "tpg_learn.h"

#include <chrono>
#include <iterator>
#include <vector>

#include "tpg_team.h"
#include "tpg_learner.h"
#include "tpg_memory_model.h"

TpgLearn::TpgLearn(std::unordered_map<std::string, double>& arguments)
{
    // Create a local reference to parameters for ease of use.
    TpgParameters& params = this->parameters;

    // Move the input argument values to the TpgParameters class.
    mergeParameters(params, arguments);

    // Create a new random number generator using the seed parameter.
    if(params.randomSeed >= 0)
    {
        // If the seed is non-negative, use it to seed the Random object.
        params.rng = *(new Random((unsigned int)arguments["seed"]));
    }
    else
    {
        // If the seed is negative, use the current time as the seed.
        params.rng = *(new Random(std::chrono::system_clock::now().time_since_epoch().count()));
    }

    // Set the uniform distribution for TPG to match the range [0.0, 1.0)
    params.distribution = std::uniform_real_distribution<double>(0.0, 1.0);

    // Initialize the Memory Model
    params.memory = new MemoryModel(params.memoryModelSize, params.learnerRegisterSize);

    // Initialize any remaining primitive parameter values
    params.nextTeamId = 0;
    params.nextLearnerId = 0;
}

TpgLearn::~TpgLearn()
{

}

bool TpgLearn::setActions(const std::vector<int64>& actions)
{
    // Create a local reference for clearer code.
    std::vector<int64>& list = this->parameters.actionList;

    // Add all of the parameter actions to the current action list.
    list.insert(list.begin(), actions.begin(), actions.end());

    // Return true if successful
    return true;
}

bool TpgLearn::initializeEnvironment()
{
    return NULL;
}

bool TpgLearn::initializePopulations()
{
    return NULL;
}

int64 TpgLearn::participate(double* inputFeatures)
{
    return NULL;
}

int64 TpgLearn::participate(double* inputFeatures, int64* actions)
{
    return NULL;
}

bool TpgLearn::rewardCurrentTeam(std::string& label, double& reward)
{
    // Create a local reference to the team queue for clearer code.
    std::queue<Team*>& teamQueue = this->parameters.teamQueue;

    // If the team queue is empty, we can't reward a Team.
    if(teamQueue.empty())
    {
        return false;
    }

    // If there is a Team at the front of the queue to reward,
    // provide them with a reward for the given task label.
    teamQueue.front()->setOutcome(label, reward);

    // Once a reward is given, remove the Team from the queue.
    teamQueue.pop();

    // We successfully rewarded a Team, so we return true.
    return true;
}

void TpgLearn::generateNewTeams()
{
    return;
}

bool TpgLearn::mutate(int64 generation, Team& team)
{
    return NULL;
}

void TpgLearn::selection()
{
    return;
}

void TpgLearn::cleanup()
{
    return;
}

void TpgLearn::nextGeneration()
{
    return;
}

void TpgLearn::printStats()
{
    return;
}

int32 TpgLearn::getRemainingTeams()
{
    return NULL;
}

int64 TpgLearn::getGenerations()
{
    return NULL;
}

std::string TpgLearn::getType()
{
    return std::string("learn");
}

void TpgLearn::mergeParameters(TpgParameters& parameters, std::unordered_map<std::string, double>& arguments)
{
    parameters.randomSeed           = static_cast<int64>(arguments["randomSeed"]);
    parameters.teamPopulationSize   = static_cast<int32>(arguments["teamPopulationSize"]);
    parameters.teamGap              = static_cast<double>(arguments["teamGap"]);
    parameters.maximumTeamSize      = static_cast<int64>(arguments["maximumTeamSize"]);
    parameters.maximumProgramSize   = static_cast<int64>(arguments["maximumProgramSize"]);
    parameters.numberOfOperations   = static_cast<int8>(arguments["numberOfOperations"]);
    parameters.probLearnerAdd       = static_cast<double>(arguments["probLearnerAdd"]);
    parameters.probLearnerDelete    = static_cast<double>(arguments["probLearnerDelete"]);
    parameters.probMutateAction     = static_cast<double>(arguments["probMutateAction"]);
    parameters.probActionIsTeam     = static_cast<double>(arguments["probActionIsTeam"]);
    parameters.probProgramAdd       = static_cast<double>(arguments["probProgramAdd"]);
    parameters.probProgramDelete    = static_cast<double>(arguments["probProgramDelete"]);
    parameters.probProgramSwap      = static_cast<double>(arguments["probProgramSwap"]);
    parameters.probProgramMutate    = static_cast<double>(arguments["probProgramMutate"]);
    parameters.learnerRegisterSize  = static_cast<int16>(arguments["learnerRegisterSize"]);
    parameters.modeSize             = static_cast<int8>(arguments["modeSize"]);
    parameters.sourceSize           = static_cast<int16>(arguments["sourceSize"]);
    parameters.memoryModelSize      = static_cast<int16>(arguments["memoryModelSize"]);
}