#include "tpg_algorithm.h"

#include <chrono>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include <vector>
#include <unordered_map>

#include "tpg_utility.h"
#include "tpg_learn.h"
#include "tpg_test.h"

#include "tpg_learner.h"
#include "tpg_team.h"


TpgAlgorithm::TpgAlgorithm(std::string_view inputFile, 
    std::string_view tpgType)
{
    // Create the initial arguments map from the parameters file.
    this->arguments = readArgumentsToMap(inputFile);
    
    // If the TPG type parameter is Learn, we should set up a TpgLearn object.
    // Otherwise we will set up a TpgTest object.
    if(std::string(tpgType).compare(std::string("learn")) == 0)
    {
        this->tpgMode = new TpgLearn(this->arguments);
    }
    else if (std::string(tpgType).compare(std::string("test")) == 0)
    {
        // TODO(Robert): This may still need the arguments list. 
        //               We'll add it after the TpgLearn bugs are worked out.
        this->tpgMode = new TpgTest();
    }
}

TpgAlgorithm::~TpgAlgorithm()
{

}

TpgMode* TpgAlgorithm::getTpgEntity()
{
    return this->tpgMode;
}

std::unordered_map<std::string, double> TpgAlgorithm::readArgumentsToMap(
    std::string_view inputFile)
{
    // Open an input file stream
    std::ifstream fileStream;

    // Open the file given in the function parameter
    fileStream.open(inputFile.data());

    // Create an unordered map for holding the parameters
    std::unordered_map<std::string, double> map;

    // Create a string for holding the line, the 
    // argument name, and the argument value
    std::string line;
    std::string argument;
    std::string value;

    // As long as the file still has lines to read, keep processing.
    while(std::getline(fileStream, line))
    {
        // Extract the argument name
        argument = line.substr(0, line.find("="));

        // Extract the argument value
        value = line.substr(line.find("=") + 1);

        // Print the argument value to the screen
        spdlog::info("ARG: {} {}", argument, value);

        // Add the argument->value pair to the unordered map using
        // the name as a string and the value as a double.
        map[argument] = std::stod(value);
    }
       
    // Return the map of parameters
    return map; 
}

///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                            MAIN LOGIC                                 //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
double actOnEnvironment(int64 action)
{
    return static_cast<double>(action * pow(100,2));
}

int main()
{
    // Set the current log level to DEBUG
    spdlog::set_level(spdlog::level::debug);

    // Set the default logger to file logger
    auto file_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt", true);
    spdlog::set_default_logger(file_logger);

    // Create the initial learning algorithm
    spdlog::debug("Creating TpgLearn Object");
    TpgAlgorithm* algorithm = new TpgAlgorithm("parameters.arg", "learn");
    spdlog::debug("TpgLearn Object Created");

    // Get the TpgLearn object
    spdlog::debug("Retrieving TpgLearn Object");
    TpgLearn& tpg = *(dynamic_cast<TpgLearn*>(algorithm->getTpgEntity()));
    spdlog::debug("Successfully Retrived TpgLearn");

    
    // Create a list of actions and give them to TpgLearn
    spdlog::debug("Creating and setting actions.");
    tpg.setActions(*(new std::vector<int64>{ 0, 1, 2, 3, 4 }));
    spdlog::debug("Actions set.");

    // Initialize TpgLearn object
    spdlog::debug("Initializing TPG...");
    tpg.initializeEnvironment();
    spdlog::debug("Initialization Complete.");

    // Create a variable for holding reward
    double reward = 0.0;

    // Create a vector for holding features
    std::vector<double>* inputFeatures = nullptr;

    // Create a variable for the number of iterations
    int numberOfIterations = 10;

    // Keep a count of the number of games to play (learning dimensions)
    int gamesToPlay = 1;

    // Main Learning Loop
    for (int i = 0; i < numberOfIterations; i++)
    {
        spdlog::debug("Enter Loop {}", i);
        for (int j = 0; j < gamesToPlay; j++)
        {
            // Let every Team play the current game once
            while (tpg.getRemainingTeams() > 0)
            {
                spdlog::debug("Start Play: Team {}", 36-tpg.getRemainingTeams());
                
                // For simulation only. See the big comment below.
                int count = 10;

                // Reset the reward to 0.
                reward = 0.0;

                // This while loop would normally be while( game.episode_still_running() ), but
                // I don't have a game to simulate for you, so here I'm simply saying that each game
                // runs for 10 "frames" before offering reward and moving to the next Team.
                while (count > 0)
                {
                    // Convert the gameState to a double[] somehow. This is a 5 feature space. A very small frame.
                    inputFeatures = new std::vector<double>{1.0, 2.1, 3.2, 4.3, 5.4};

                    // Accumulate the reward by getting TPG to play. TPG receives the input features,
                    // then returns an action label, which is enacted on the environment. The environment
                    // then returns a reward which can be applied immediately or stored for later use,
                    // depending on what you want the algorithm to do.
                    spdlog::debug("Get Reward {},{}", i, j);
                    reward += actOnEnvironment(tpg.participate(*inputFeatures));

                    // Counting down frames for testing purposes
                    count--;
                }

                // Reward the current Team. This automatically rotates the current Team.
                // The "game" string should be unique to the game the Team just played.
                // In single-game learning just make it static, but when you move on to
                // playing multiple games, you'll need to make sure the labels are correct.
                tpg.rewardCurrentTeam("game", reward);
                spdlog::debug("Reward = {}", reward);
            }
        }
        
        // Print the current top 10 Team population outcomes and some simple environment values
        spdlog::debug("Print Stats {}", i);
        printf("Print Stats %d\n", i);
        tpg.printStats(10, "game");

        // Tell TPG to initiate a reproduction cycle
        printf("Reproduce %d\n", i);
        spdlog::debug("Reproduce {}", i);
        tpg.executeReproduction();

        // Reset TPG so it increases the generation count and finds the new Root Teams
        spdlog::debug("Move From {} to {}", i, i+1);
        printf("Next Generation %d\n", i);
        tpg.nextGeneration();
        printf("New Generation %d\n", i+1);
    }

    return 0;
}