#include "tpg_learn.h"

#include <chrono>
#include <iterator>
#include <vector>

#include "tpg_default_reproduction.h"
#include "tpg_team.h"
#include "tpg_learner.h"
#include "tpg_memory_model.h"

TpgLearn::TpgLearn(std::unordered_map<std::string, double>& arguments)
{
    // Create a local reference to parameters for ease of use.
    TpgParameters& params = this->parameters;

    // Move the input argument values to the TpgParameters class.
    mergeParameters(params, arguments);

    spdlog::debug("Finished merging the arguments");
    
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

    // Initialize the Reproduction Model
    params.reproduction = new StandardReproduction();

    // Initialize any remaining primitive parameter values
    params.nextTeamId = 0;
    params.nextLearnerId = 0;
    params.generation = -1;
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
    // If we fail to initialize the team and learner populations,
    // we should fail the entire initialization process.
    if(!initializePopulations())
    {
        return false;
    }
    
    // Add every root team to the team queue.
    for(Team* rootTeam : this->parameters.rootTeamPopulation)
    {
        this->parameters.teamQueue.push(rootTeam);
    }

    // Set the generation to 0.
    parameters.generation = 0;

    // If nothing failed during this process, we can return true.
    return true;
}

bool TpgLearn::initializePopulations()
{
    // Create local references for cleaner code.
    std::vector<Team*>& rootTeamPopulation = this->parameters.rootTeamPopulation;
    std::vector<Team*>& teamPopulation = this->parameters.teamPopulation;
    std::vector<Learner*>& learnerPopulation = this->parameters.learnerPopulation;
    std::vector<int64>& actions = this->parameters.actionList;

    // Create a Team pointer and a Learner pointer for storing objects.
    Team* team = nullptr;
    Learner* learner = nullptr;

    // Create enough teams to fill the team population.
    for(int i=0; i < parameters.teamPopulationSize; ++i)
    {
        // Generate two relatively unique random actions from the action list.
        int64 action1 = parameters.rngInt64(0, actions.size());
        int64 action2 = 0;

        // The second action generated must not be the same as the first.
        do
        {
            action2 = parameters.rngInt64(0, actions.size());
        } while (action1 == action2);

        // Use the indexes held in the action variables to overwrite
        // the indexes with action values.
        action1 = actions[action1];
        action2 = actions[action2];

        // Create a new Team for the pre-learning generation -1.
        team = new Team(this->parameters);

        // Create the first Learner for the Team.
        learner = new Learner(action1, this->parameters);

        // Add the new Learner to the Team.
        team->addLearner(*learner);

        // Add the new Learner to the Learner population.
        learnerPopulation.push_back(learner);

        // Create the second Learner for the Team.
        learner = new Learner(action2, this->parameters);

        // Add the new Learner to the Team.
        team->addLearner(*learner);

        // Add the new Learner to the Learner population.
        learnerPopulation.push_back(learner);

        // Calculate the number of additional Learners to generate,
        // to a maxmimum of the maximum team size.
        int64 extraLearners = this->parameters.rngInt64(0, this->parameters.maximumTeamSize - 2);

        // Create the number of extra Learners
        for(int j=0; j < extraLearners; ++j)
        {
            // Uniformly generate a new atomic action.
            action1 = actions[this->parameters.rngInt64(0, actions.size())];

            // Create a new Learner with that atomic action.
            learner = new Learner(action1, this->parameters);

            // Add the Learner to the Team and the Learner population
            team->addLearner(*learner);
            learnerPopulation.push_back(learner);
        }

        // Add the completed team to the team and root team populations.
        teamPopulation.push_back(team);
        rootTeamPopulation.push_back(team);
    }

    // We've generated all the teams successfully; return true
    return true;
}

int64 TpgLearn::participate(std::vector<double>& inputFeatures)
{
    // If there are no Teams left to play, then this learning phase
    // is over. Return -1 to indicate end-of-play.
    spdlog::debug("PARTICIPATE: RootPopSize = {}", this->parameters.teamQueue.size());
    if(this->parameters.teamQueue.empty())
    {
        return -1;
    }
    
    // If we have a team, we can get it from the front of the queue.
    Team* team = this->parameters.teamQueue.front();

    spdlog::debug("PARTICIPATE: TeamID = {}", team->getId());

    // Provide the team with the input parameters and an empty unordered
    // set, then return the action it suggests.
    return team->getAction(*(new std::unordered_set<Team*>()), 
        inputFeatures, this->parameters);
}

int64 TpgLearn::participate(std::vector<double>& inputFeatures, 
    std::vector<int64>& actions)
{
    // Use the single-parameter participate function to get an action
    // from the first team in the team queue.
    int64 action = this->participate(inputFeatures);

    // If the action returned is in the action list, return it.
    for(int i=0; i < this->parameters.actionList.size(); ++i)
    {
        if(this->parameters.actionList[i] == action)
        {
            return action;
        }
    }

    // If the action is not in the action list, return a default of 0.
    return 0;
}

bool TpgLearn::rewardCurrentTeam(std::string_view label, double& reward)
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

void TpgLearn::executeReproduction()
{
    // Create local references for cleaner code.
    std::vector<Team*>& rootTeamPopulation = this->parameters.rootTeamPopulation;
    std::vector<Team*>& teamPopulation = this->parameters.teamPopulation;
    std::vector<Learner*>& learnerPopulation = this->parameters.learnerPopulation;
    Reproduction* reproduction = this->parameters.reproduction;

    // Force every root team to calculate their current fitness.
    printf("REPRO: Calculating Fitness\n");
    for(Team* team : rootTeamPopulation)
    {
        team->calculateFitness();
    }

    // The first step is to run selection on the root team population.
    // This ranks the root teams by their current citness and then
    // removes the bottom half of the root team population. The original
    // root teams will still be intact, which could cause issues.
    printf("Team Population:\n");
    for (Team* T : teamPopulation)
        printf("%llu ", T->getId());
    printf("\n");

    printf("Root Team Population:\n");
    for (Team* T : rootTeamPopulation)
        printf("%llu ", T->getId());
    printf("\n");

    printf("REPRO: Selection Start\n");
    std::vector<Team*> rankedTeams = reproduction->teamSelection(
        rootTeamPopulation, this->parameters);

    printf("Ranked: ");
    for (Team* T : rankedTeams)
        printf("%llu ", T->getId());
    printf("\n");

    // Once the teams are ranked and the gap is removed, we then 
    // use those teams to reproduce to bring the population back up.
    printf("REPRO: Reproduction Start\n");
    std::vector<Team*> childTeams = reproduction->teamReproduction(
        rankedTeams, this->parameters);

    printf("Child: ");
    for (Team* T : childTeams)
        printf("%llu ", T->getId());
    printf("\n");

    // Now that the child teams have been created, we can then mutate
    // each of them.
    printf("REPRO: Mutation Start\n");
    std::vector<Team*> mutatedTeams = reproduction->teamMutation(
        childTeams, this->parameters);

    printf("Mutate: ");
    for (Team* T : mutatedTeams)
        printf("%llu ", T->getId());
    printf("\n");

    // The teamSelection(..) method has already removed the relevant
    // bottom half root teams from the applicable populations, so we
    // can now add the mutated children to the team population.
    printf("REPRO: Unification Start\n");
    teamPopulation.insert(teamPopulation.end(), mutatedTeams.begin(), mutatedTeams.end());

    printf("Unification Result:\n");
    for (Team* T : teamPopulation)
        printf("%llu ", T->getId());
    printf("\n");

}

void TpgLearn::cleanup()
{
    // Create local references for cleaner code.
    std::vector<Learner*>& learnerPopulation = this->parameters.learnerPopulation;

    // Create a copy of the Learner population.
    std::vector<Learner*> allLearners = learnerPopulation;

    // Iterate through all the Learners in the population.
    for(Learner* learner : allLearners)
    {
        // If the current Learner has nothing referencing it,
        // we should remove it from the population and delete it.
        if(learner->getReferences() == 0)
        {
            // Find an iterator which points to the location in the
            // Learner population where this Learner is stored.
            auto position = std::find_if(
                learnerPopulation.begin(),
                learnerPopulation.end(),
                [learner](Learner* l) {return *l == *learner;}
            );

            // Erase the Learner data in that position of the vector.
            learnerPopulation.erase(position);

            // If the Learner is holding a reference to a Team,
            // we should decrease the references to that Team by 1.
            if(!learner->getActionObject()->isAtomicAction())
            {
                learner->getActionObject()->getTeam()->decreaseReferences();
            }

            // Finally, delete the Learner.
            delete learner;
        }
    }

    // Explicit return to signify the end of the method.
    return;
}

int64 TpgLearn::nextGeneration()
{
    // Create local references for cleaner code.
    std::vector<Team*>& rootTeams = this->parameters.rootTeamPopulation;
    std::vector<Team*>& teams = this->parameters.teamPopulation;
    std::queue<Team*>& teamQueue = this->parameters.teamQueue;

    // Execute the cleanup cycle to finalize this generation.
    this->cleanup();

    // Clear the outcome map of every Team.
    for(Team* team : teams)
    {
        team->clearOutcomes();
    }

    // Clear the current root team population.
    rootTeams.erase(rootTeams.begin(), rootTeams.end());

    // Populate the root teams population from the team population.
    for(Team* team : teams)
    {
        // If the current team has an in-degree of 0,
        // then we add it to the root teams vector.
        if (team->getReferences() == 0)
        {
            rootTeams.push_back(team);
        }
    }

    // Ensure there's nothing stored in the team queue.
    while(!teamQueue.empty())
    {
        teamQueue.pop();
    }

    // Add all the root teams to the team queue.
    for(Team* team : rootTeams)
    {
        teamQueue.push(team);
    }

    // Increase the generations by 1 and return the new value.
    return ++(this->parameters.generation);
}

void TpgLearn::printStats(int32 count, std::string_view label)
{
    std::vector<Team*>& rootTeams = this->parameters.rootTeamPopulation;
    
    int32 limit = count > rootTeams.size() ? count : static_cast<int32>(rootTeams.size());

    for(int i = 0; i < limit; i++)
    {
        spdlog::info("Gen {}, Rank {}: {} = {}",
            this->parameters.generation,
            i + 1,
            rootTeams[i]->getId(),
            rootTeams[i]->getOutcome(label.data()));
    }
}

int32 TpgLearn::getRemainingTeams()
{
    // Return the size of the team queue.
    return static_cast<int32>(this->parameters.teamQueue.size());
}

int64 TpgLearn::getGenerations()
{
    // Return the current generation value.
    return this->parameters.generation;
}

std::string TpgLearn::getType()
{
    return std::string("learn");
}

void TpgLearn::mergeParameters(TpgParameters& parameters, std::unordered_map<std::string, double>& arguments)
{
    parameters.randomSeed            = static_cast<int64>(arguments["randomSeed"]);
    parameters.teamPopulationSize    = static_cast<int32>(arguments["teamPopulationSize"]);
    parameters.teamGap               = static_cast<double>(arguments["teamGap"]);
    parameters.maximumTeamSize       = static_cast<int64>(arguments["maximumTeamSize"]);
    parameters.minimumTeamSize       = static_cast<int64>(arguments["minimumTeamSize"]);
    parameters.minimumRootTeams      = static_cast<int64>(arguments["minimumRootTeams"]);
    parameters.maximumProgramSize    = static_cast<int64>(arguments["maximumProgramSize"]);
    parameters.numberOfOperations    = static_cast<int8>(arguments["numberOfOperations"]);
    parameters.probLearnerAdd        = static_cast<double>(arguments["probLearnerAdd"]);
    parameters.probLearnerDelete     = static_cast<double>(arguments["probLearnerDelete"]);
    parameters.probLearnerMutate     = static_cast<double>(arguments["probLearnerMutate"]);
    parameters.probMutateAction      = static_cast<double>(arguments["probMutateAction"]);
    parameters.probActionIsTeam      = static_cast<double>(arguments["probActionIsTeam"]);
    parameters.probInstructionAdd    = static_cast<double>(arguments["probInstructionAdd"]);
    parameters.probInstructionDelete = static_cast<double>(arguments["probInstructionDelete"]);
    parameters.probInstructionSwap   = static_cast<double>(arguments["probInstructionSwap"]);
    parameters.probInstructionMutate = static_cast<double>(arguments["probInstructionMutate"]);
    parameters.learnerRegisterSize   = static_cast<int16>(arguments["learnerRegisterSize"]);
    parameters.modeSize              = static_cast<int8>(arguments["modeSize"]);
    parameters.sourceSize            = static_cast<int16>(arguments["sourceSize"]);
    parameters.memoryModelSize       = static_cast<int16>(arguments["memoryModelSize"]);
}