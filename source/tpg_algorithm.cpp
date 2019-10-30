#include "tpg_algorithm.h"

#include <chrono>
#include <iostream>
#include <fstream>

#include <vector>
#include <unordered_map>

#include "tpg_utility.h"
#include "tpg_learn.h"
#include "tpg_test.h"

#include "tpg_learner.h"
#include "tpg_team.h"


TpgAlgorithm::TpgAlgorithm(const char* inputFile, const char* tpgType)
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
        this->tpgMode = new TpgTest();
    }
}

TpgAlgorithm::~TpgAlgorithm()
{

}

void TpgAlgorithm::startLearning(std::string*)
{
    return;
}

void TpgAlgorithm::startTesting(std::string*)
{
    return;
}

TpgMode* TpgAlgorithm::getTpgMode()
{
    return this->tpgMode;
}

std::unordered_map<std::string, double> TpgAlgorithm::readArgumentsToMap(const char* inputFile)
{
    // Open an input file stream
    std::ifstream fileStream;

    // Open the file given in the function parameter
    fileStream.open(inputFile);

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
        std::cout << "ARG: " << argument << " " << value << "\n";

        // Add the argument->value pair to the unordered map using
        // the name as a string and the value as a double.
        map[argument] = std::stod(value);
    }
       
    // Return the map of parameters
    return map; 
}

///////////////////////////////////////////////////////////////////////////
//                                                                       //
//                           MAIN FUNCTION                               //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
int main()
{
    printf("Main Function Called\n");

    TpgAlgorithm* algorithm = new TpgAlgorithm("parameters.arg", "learn");

    return 0;
}