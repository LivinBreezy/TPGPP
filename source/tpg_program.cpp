
#include "tpg_program.h"

#include "tpg_utility.h"

/**
 *  @brief     Constructor for creating a new random Program.
 *  @details   This constructor uses the base TPG parameters, such as the stored
 *  random number generator, the maximum program size, and the operator map to
 *  create a random Program which fits the bounds of the current environment.
 *  This includes generating all the Instruction objects up to the maximum
 *  program size and initializing the general purpose registers.
 *  @param parameters A struct held by the main TPG algorithm objects
 *  (TpgLearn or TpgPlay) and stores all of the current parameter values 
 *  for the current environment.
 *  @todo      Implementation and full commenting required.
 */
Program::Program(const TpgParameters& parameters)
{
    this->instructions = {};
    this->registers = nullptr;
    this->maximumProgramSize = NULL;
}

/**
 *  @brief     Constructor for creating a copy of another Program.
 *  @details   This constructor accepts another Program object pointer and
 *  makes a deep copy. The original Program is not altered and the new Program
 *  will hold any state currently held by the original Program.
 *  @param     other A pointer to a Program object to be copied.
 *  @todo      Implementation and full commenting required.
 */
Program::Program(const Program& other, TpgParameters& parameters)
{
    this->instructions = {};
    this->registers = nullptr;
    this->maximumProgramSize = NULL;
}

Program::Program(std::vector<Instruction>& instructionList)
{
    this->instructions = new std::vector<Instruction>(instructionList);
    this->registers = nullptr;
    this->maximumProgramSize = NULL;
}

/**
 *  @brief     Destructor for freeing a Program.
 *  @details   This destructor frees all Instructions, frees its register
 *  set, then ends.
  *  @todo      Implementation and full commenting required.
 */
Program::~Program()
{

}

/**
 *  @brief     Execute a Program on the provided feature set.
 *  @details   Upon receiving a feature set, this method will execute each
 *  stored Instruction on the feature set in conjuction with the general
 *  purpose registers held by this Program, then return the first value
 *  in the registers as a bid value.
 *  @param     inputFeatures A double array representing the environment's
 *  complete feature set.
 *  @return    A double value representing a Learner bid.
 *  @todo      Implementation and full commenting required.
 */
double Program::execute(const std::vector<double>& inputFeatures)
{
    return NULL;
}

/**
 *  @brief     Mutate the Instructions in a Program.
 *  @details   Uses the given parameters to mutate this Program object.
 *  This can include changing the mode value, the source/destination
 *  indexes, and/or the operation of the Instructions.
 *  @param     parameters A struct held by the main TPG algorithm objects
 *  (TpgLearn or TpgPlay) and stores all of the current parameter values
 *  for the current environment.
 *  @return    A boolean value which is true if Instructions were mutated.
 *  Otherwise return false.
 *  @todo      Implementation and full commenting required.
 */
bool Program::mutate(const TpgParameters& parameters)
{
    return NULL;
}

/**
 *  @brief     Return the number of Instructions with the parameter name.
 *  @details   Upon receiving a string, this method searches the Instruction
 *  list for any operations with the same name and counts them. It then returns
 *  that value as a 32-bit integer.
 *  @param     operationName A pointer to a string holding the name of an 
 *  operation.
 *  @return    A 32-bit integer representing the number of times the given
 *  operator was found.
 *  @todo      Implementation and full commenting required.
 */
int32 Program::instructionCount(const std::string& operationName) const
{
    return NULL;
}

/**
 *  @brief     Return the number of Instructions of each operator type.
 *  @details   Using the operations map from the parameters, this method
 *  creates a map which contains the number of each type of Instruction,
 *  where the key->value pair is represented as operatorName->count. Once
 *  the map is completed, it is returned.
 *  @param     parameters A struct held by the main TPG algorithm objects
 *  (TpgLearn or TpgPlay) and stores all of the current parameter values 
 *  for the current environment.
 *  @return    A string->int32 map containing the number of types each
 *  operation appears in the Instructions list.
 *  @todo      Implementation and full commenting required.
 */
std::map<std::string, int32>* Program::allInstructionCounts(const TpgParameters& parameters) const
{
    return nullptr;
}

std::vector<Instruction>* Program::getInstructions() const
{
    return instructions;
}

/**
 *  @brief     Return a string representation of a Program object.
 *  @details   TBD. It could be a full Instruction list in plain language.
 *  @return    A pointer to a string, which represents a Program object.
 *  @todo      Implementation and full commenting required.
 */
std::string* Program::toString() const
{
    return nullptr;
}