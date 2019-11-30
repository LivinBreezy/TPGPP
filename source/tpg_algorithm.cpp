#include "tpg_algorithm.h"

#include <chrono>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <limits>

#include <vector>
#include <unordered_map>

#include <boost/serialization/split_member.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "tpg_utility.h"
#include "tpg_learn.h"
#include "tpg_test.h"

#include "tpg_learner.h"
#include "tpg_team.h"

//remove
#include "tpg_action.h"


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

class Test
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void save(Archive& ar, const unsigned int version)
    {
        ar & a;
    }

    template<class Archive>
    void load(Archive& ar, const unsigned int version)
    {
        ar & a;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    bool a;

public:
    Test() { a = true; };
};

int main()
{
    //Action* act = new Action(55);
    //std::ofstream ofs("tmp.dat");
    //boost::archive::text_oarchive ar(ofs);
    //ar & act;

    Test* test = new Test();
    std::ofstream ofs("tmp.dat");
    boost::archive::text_oarchive ar(ofs);
    ar & test;

    // Set the current log level to DEBUG
    spdlog::set_level(spdlog::level::debug);

    // Set the default logger to file logger
    auto file_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt", true);
    spdlog::set_default_logger(file_logger);

    // Create the initial learning algorithm
    TpgAlgorithm* algorithm = new TpgAlgorithm("parameters.arg", "learn");

    // Get the TpgLearn object
    TpgLearn& tpg = *(dynamic_cast<TpgLearn*>(algorithm->getTpgEntity()));
       
    // Create a list of actions and give them to TpgLearn
    tpg.setActions(*(new std::vector<int64>{ 0, 1, 2, 3, 4 }));

    // Initialize TpgLearn object
    tpg.initializeEnvironment();

    printf("Initialization Complete\n");

    // Create a variable for holding reward
    double reward = 0.0;

    // Create a vector for holding features
    std::vector<double>* inputFeatures = nullptr;

    // Create a variable for the number of iterations
    int numberOfIterations = 10;

    // Keep a count of the number of games to play (learning dimensions)
    int gamesToPlay = 1;

    time_t startTime;

    // Main Learning Loop
    for (int i = 0; i < numberOfIterations; i++)
    {
        startTime = time(nullptr);
        for (int j = 0; j < gamesToPlay; j++)
        {
            // Let every Team play the current game once
            while (tpg.getRemainingTeams() > 0)
            {
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
                    reward += actOnEnvironment(tpg.participate(*inputFeatures));

                    // Counting down frames for testing purposes
                    count--;
                }

                // Reward the current Team. This automatically rotates the current Team.
                // The "game" string should be unique to the game the Team just played.
                // In single-game learning just make it static, but when you move on to
                // playing multiple games, you'll need to make sure the labels are correct.
                tpg.rewardCurrentTeam("game", reward);
            }
        }
        
        // Print the current top 10 Team population outcomes and some simple environment values
        tpg.printStats(10, "game");

        // Tell TPG to initiate a reproduction cycle
        tpg.executeReproduction();

        // Reset TPG so it increases the generation count and finds the new Root Teams
        tpg.nextGeneration();
        printf("New Generation %d: %f seconds\n", i+1, difftime(time(nullptr), startTime));
    }

    return 0;
}