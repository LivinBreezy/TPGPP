#include "tpg_default_reproduction.h"

#include <vector>

#include "tpg_utility.h"
#include "tpg_reproduction.h"
#include "tpg_team.h"
#include "tpg_learner.h"
#include "tpg_action.h"
#include "tpg_program.h"
#include "tpg_instruction.h"

bool compareSingleOutcome(const Team* a, const Team* b)
{
    return a->getFitness() > b->getFitness();
}

std::vector<Team*> StandardReproduction::teamSelection(std::vector<Team*>& teams,
    TpgParameters& parameters)
{
    // Make a copy of the incoming Team vector.
    std::vector<Team*> rankedTeams = std::vector<Team*>(teams);

    // Sort all of the Teams by their first (and only) outcome.
    std::sort(rankedTeams.begin(), rankedTeams.end(), compareSingleOutcome);

    // Return the ranked vector of Teams.
    return rankedTeams;
}

std::vector<Team*> StandardReproduction::teamReproduction(std::vector<Team*>& parentTeams,
    TpgParameters& parameters)
{
    // Create a new vector for holding the child teams.
    std::vector<Team*> childTeams;

    // Iterate through all of the parent teams.
    for(Team* parent : parentTeams)
    {
        // Create a new child, made on the current generation.
        Team* child = new Team(parameters.generation, parameters);

        // Add every learner on the parent team to the child team.
        for(Learner* learner : parent->getLearners())
        {
            child->addLearner(*learner);
        }

        // Add the child team to the child team vector.
        childTeams.push_back(child);
    }

    // Return the child team vector.
    return childTeams;
}

std::vector<Team*> StandardReproduction::teamMutation(std::vector<Team*>& childTeams,
    TpgParameters& parameters)
{
    // Create local references for cleaner code.
    std::vector<Learner*>& learners = parameters.learnerPopulation;
    
    // Create a copy of the child teams vector.
    std::vector<Team*> mutatedTeams = std::vector<Team*>(childTeams);

    // Iterate through all of the teams in the mutated teams list.
    for(Team* team : mutatedTeams)
    {
        // If we hit our target probability for deleting learners from
        // teams, run the learner deletion cycle.
        if(parameters.rngUniform() < parameters.probLearnerDelete)
        {
            // Create a double for holding the cumulative probability.
            double cumulative = 1.0;
            
            // Create a 32-bit integer for storing a vector index.
            int64 index = 0;
            
            // As long as the Team has enough learners that it can still
            // safely lose one and the cumulative probability is hit,
            // randomly remove a learner.
            while(team->numberOfLearners() > parameters.minimumTeamSize
                && parameters.rngUniform() < cumulative)
            {
                // Create a variable for holding a learner pointer.
                Learner* learner = nullptr;
                
                // Continue randomly attempting to remove learners
                // until one is successfully removed.
                do
                {
                    // Get the index of a random learner from the team.
                    index = parameters.rngInt64(0, team->numberOfLearners());

                    // Retrieve the learner to be deleted and store it.
                    learner = team->getLearners()[index];
                } 
                while (team->removeLearner(*learner) == false);

                // Update the cumulative probability.
                cumulative *= parameters.probLearnerDelete;
            }
        }

        // If we hit our target probability for adding learners to teams, run 
        // the learner add cycle.
        if (parameters.rngUniform() < parameters.probLearnerAdd)
        {
            // Create a double for holding the cumulative probability.
            double cumulative = 1.0;

            // Create a 32-bit integer for storing a vector index.
            int64 index = 0;

            // As long as the Team has enough space for new learners,
            // and the cumulative probability is hit, randomly add a 
            // learner from the learner population.
            while (team->numberOfLearners() < parameters.maximumTeamSize
                && parameters.rngUniform() < cumulative)
            {
                // Create a variable for holding a learner pointer.
                Learner* learner = nullptr;

                // Continue randomly attempting to add learners until 
                // one is successfully added. We cannot add a learner 
                // which already exists on the team.
                do
                {
                    // Get the index of a random learner from the 
                    // learner population.
                    index = parameters.rngInt64(0, learners.size());

                    // Retrieve the learner to be added and store it.
                    learner = learners[index];
                } 
                while(team->addLearner(*learner) == false);

                // Update the cumulative probability.
                cumulative *= parameters.probLearnerAdd;
            }
        }

        // Make a copy of the team's learner vector.
        std::vector<Learner*> originalLearners = std::vector<Learner*>(team->getLearners());

        // Iterate through all the original learners.
        for(Learner* learner : originalLearners)
        {
            // If we hit our target probability for mutating a learner,
            // proceed through the Learner mutation algorithm.
            if(parameters.rngUniform() < parameters.probLearnerMutate)
            {
                // Retrieve a copy of the original learner's program.
                Program program = learner->getProgram();

                // Perform the Program mutation cycle on the new Learner
                // and store it in a new variable.
                Program newProgram = mutateProgram(program, parameters);

                // Delete the old program copy.
                delete &program;

                // Remove the original learner from the team.
                team->removeLearner(*learner);

                // Extract the action from the original learner.
                Action* action = learner->getActionObject();

                // If we hit the target probability for mutating a learner's
                // action, we proceed through the algorithm.
                if(parameters.rngUniform() < parameters.probMutateAction)
                {
                    action = &(mutateAction(*action, parameters));
                }               

                // Create a pointer for holding a new learner.
                Learner* newLearner = nullptr;

                // Create the new learner and store it based on its action type.
                if(action->isAtomicAction())
                {
                    // The learner is created with an atomic action.
                    newLearner = new Learner(
                        parameters.nextLearnerId++,
                        parameters.generation,
                        action->getAtomic(),
                        0,
                        newProgram
                    );
                }
                else
                {
                    // The learner is created with a team reference action.
                    newLearner = new Learner(
                        parameters.nextLearnerId++,
                        parameters.generation,
                        *(action->getTeam()),
                        0,
                        newProgram
                    );
                }

                // Add the new learner to the team.
                team->addLearner(*newLearner);

                // Add the new learner to the learner population
                learners.push_back(newLearner);
            }
        }
    }

    // Return the vector of mutated teams.
    return mutatedTeams;
}

Program StandardReproduction::mutateProgram(Program& program, TpgParameters& parameters)
{
    // Create a copy of the instruction set from the program object.
    std::vector<Instruction> instructions = *(new std::vector<Instruction>(*(program.getInstructions())));

    // Create a variable for holding random index values.
    int64 index = 0;

    // Create a boolean for ensuring at least one mutation occurred.
    bool mutated = false;

    // As long as we haven't mutated, keep attempting to perform mutations.
    while (!mutated)
    {
        // Attempt to remove a random instruction by probability.
        if (parameters.rngUniform() < parameters.probInstructionDelete)
        {
            // Generate a random index for the instruction vector.
            index = parameters.rngInt64(0, instructions.size());

            // Remove the instruction from the random index.
            instructions.erase(instructions.begin() + index);
            delete& (instructions.begin() + index);

            // If this change was successful, then we've mutated.
            mutated = true;
        }

        // Attempt to insert a random instruction at a random location
        // by probability.
        if (parameters.rngUniform() < parameters.probInstructionAdd)
        {
            // Create a new random instruction.
            Instruction* instruction = new Instruction(parameters);

            // Generate a random index for the instruction vector.
            index = parameters.rngInt64(0, instructions.size());

            // Insert the new instruction at the random location.
            instructions.insert(instructions.begin() + index, *instruction);

            // If this change was successful, then we've mutated.
            mutated = true;
        }

        // Mutate a random instruction.
        if (parameters.rngUniform() < parameters.probInstructionMutate)
        {
            // Generate a random index for the instruction vector.
            index = parameters.rngInt32(0, instructions.size());

            // Mutate a new instruction from the old one at the random index.
            Instruction instruction = mutateInstruction(instructions[index], parameters);

            // Remove the old instruction and replace it with the new one.
            delete& (instructions.begin() + index);
            instructions.erase(instructions.begin() + index);
            instructions.insert(instructions.begin() + index, instruction);

            // If this change was successful, then we've mutated.
            mutated = true;
        }

        // Swap the position of two instructions
        if (parameters.rngUniform() < parameters.probInstructionSwap)
        {
            // Create a variable and generate a random index for the
            // instruction vector.
            int32 other = parameters.rngInt32(0, instructions.size());

            // Generate a random index which is different from our first
            // random index.
            do
            {
                index = parameters.rngInt32(0, instructions.size());
            } 
            while (index != other);

            // Create a variable for holding an Instruction temporarily.
            Instruction* temp = 0;

            // Swap the instructions with a three-point replacement.
            temp = &(instructions[index]);
            instructions[index] = instructions[other];
            instructions[other] = *temp;

            // If this change was successful, then we've mutated.
            mutated = true;
        }
    }

    // Return a copy of the new program with the mutated instructions
    return *(new Program(instructions));
}

Instruction StandardReproduction::mutateInstruction(Instruction& instruction, TpgParameters& parameters)
{
    // Choose one of the categories to mutate uniformly.
    int32 category = parameters.rngInt32(0, 4);

    // Store each component of the original instruction locally.
    int8 mode = instruction.getMode();
    int32 source = instruction.getSource();
    int8 destination = instruction.getDestination();
    Operation* operation = instruction.getOperation();

    // Switch across the category value to decide which category to mutate.
    switch(category)
    {
        case 0:
        {   
            // Create a variable for holding a random mode value.
            int8 newMode = 0;
            
            // Randomly generate mode values until it does not match
            // the original mode value.
            do
            {
                newMode = parameters.rngInt8(0, parameters.modeSize);
            } 
            while (newMode == mode);
            
            // Overwrite the old mode value with the mutated version.
            mode = newMode;
            
            // Break the switch.
            break;
        }
        case 1:
        {
            // Create a variable for holding a random source value.
            int32 newSource = 0;
            
            // Randomly generate source values until it does not match
            // the original source value.
            do
            {
                newSource = parameters.rngInt32(0, parameters.sourceSize);
            } 
            while (newSource == source);
            
            // Overwrite the old source value with the mutated version.
            source = newSource;
            
            // Break the switch.
            break;
        }
        case 2:
        {
            // Create a variable for holding a random destination value.
            int8 newDestination = 0;

            // Randomly generate mode values until it does not match
            // the original mode values.
            do
            {
                newDestination = parameters.rngInt8(0, parameters.learnerRegisterSize);
            } 
            while (newDestination == destination);
            
            // Overwrite the old mode destination with the mutated version.
            destination = newDestination;
            
            // Break the switch.
            break;
        }
        case 3:
        {
            // Create a variable for holding a random operation pointer.
            Operation* newOperation = nullptr;
            
            // Randomly generate operations until it does not match
            // the original operation.
            do
            {
                newOperation = &(Instruction::createOperationOfType(
                    parameters.rngInt8(0, parameters.numberOfOperations)
                ));
            } 
            while (newOperation->toString().compare(operation->toString()) == 0);
            
            // Store the new operation.
            operation = newOperation;
            
            // Break the switch.
            break;
        }
    }

    // Create a new instruction using the up-to-date values.
    return *(new Instruction(mode, source, destination, operation));
}

Action StandardReproduction::mutateAction(Action& action, TpgParameters& parameters)
{
    // Create a pointer for holding an action.
    Action* newAction = nullptr;

    // Create a variable for holding a vector index.
    int64 index = 0;

    // Randomly decide if the mutated action should be atomic or a team.
    if(parameters.rngUniform() < parameters.probActionIsTeam)
    {
        // Create local references for cleaner code.
        std::vector<Team*>& rootTeams = parameters.rootTeamPopulation;
        std::vector<Team*>& teams = parameters.teamPopulation;
        
        // Create a pointer for holding a Team.
        Team* newTeam = nullptr;

        // Create an auto for holding team iterators.
        std::vector<Team*>::iterator foundTeam;

        // Repeatedly try to find a team based on the root team size.
        // If we randomly choose a root team and we're at the minimum number
        // of root teams already, we can't let that root team disappear,
        // so we select a new team instead. We also can't choose the same team
        // if the current action is using it.
        do
        {
            // Generate a value for a random index in the team population.
            index = parameters.rngInt64(0, teams.size());

            // Store the random team locally.
            newTeam = teams[index];

            // Search the root teams vector to see if the new team is in it.
            foundTeam = std::find_if(
                rootTeams.begin(),
                rootTeams.end(),
                [newTeam](Team* t) {return *t == *newTeam;}
            );
        } 
        while(static_cast<int64>(rootTeams.size()) <= parameters.minimumRootTeams
            && foundTeam != rootTeams.end()
            || (!action.isAtomicAction() && action.getTeam()->getId() == newTeam->getId()));

        // Once we find a valid team, create a new 
        // Action object for holding it.
        newAction = new Action(*newTeam);
    }
    else
    {
        // Create local references for cleaner code
        std::vector<int64>& actions = parameters.actionList;

        // Create a variable for storing the new atomic action.
        int64 newAtomic = 0;

        // Randomly select a new action from the list. If it's the
        // one already contained in the action, we randomize a new one.
        do
        {
            // Generate a value for a random index in the action list.
            index = parameters.rngInt64(0, actions.size());

            // Store the random action locally.
            newAtomic = actions[index];
        } 
        while (action.isAtomicAction() && action.getAtomic() == newAtomic);

        // Once we find a valid atomic, create a new
        // Action object for holding it.
        newAction = new Action(newAtomic);
    }
    
    // Return a copy of the mutated action.
    return *newAction;
}