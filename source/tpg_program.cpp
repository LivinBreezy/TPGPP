
#include "tpg_program.h"

#include <vector>

#include "tpg_utility.h"

///////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTOR
///////////////////////////////////////////////////////////////////////////////

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
Program::Program(TpgParameters& parameters)
{
    // generate new random instructions
    this->instructions = new std::vector<Instruction>();
    int64 numInstructions = parameters.rngInt64(1, parameters.maximumProgramSize);
    for (int64 i = 0; i < numInstructions; ++i)
    {
        this->instructions->push_back(Instruction(parameters));
    }

    // initialize registers to 0
    this->registers = new std::vector<double(parameters.learnerRegisterSize, 0);
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
    // copy instructions of other
    this->instructions = new std::vector<Instruction>(*other.instructions);

    // initialize registers to other's registers
    this->registers = program.registers;
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
 *  @todo      Testing required.
 */
Program::~Program()
{
    delete instructions;
    delete[] registers;
}

///////////////////////////////////////////////////////////////////////////////
// GETTERS AND SETTERS
///////////////////////////////////////////////////////////////////////////////

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
 *  @todo      Implementation and full commenting required. Implement later
 *  once Instruction is finalized.
 */
int64 Program::instructionCount(const std::string_view& operationName) const
{
    int64 count = 0;

    for (Instruction inst : instructions) {
        if (inst.getType().compare(operationName)) {
            // found an instruction of this type
            ++count;
        }
    }

    return count;
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
std::unordered_map<std::string, int64> Program::allInstructionCounts(const TpgParameters& parameters) const
{
    std::unordered_map<std::string, int64> countMap = 
        std::unordered_map<std::string, int64>();

    Instruction inst = NULL;

    std::vector<std::string> instTypes;

    // get all instruction types
    for (int8 i = 0; i < parameters.numberOfOperations; ++i)
    {
        // put key in count map
        inst = Instruction(0, 0, 0, &Instruction::createOperationOfType(i));
        countMap.emplace(inst.getType(), 0);

        // track type name
        instTypes.push_back(inst.getType());
    }

    // find counts
    for (Instruction inst : instructions) 
    {
        for (std::string instType : instTypes) 
        {
            if (inst.getType().compare(instType)) 
            {
                ++countMap.at(instType);

                break;
            }
        }
    }

    return countMap;
}

std::vector<Instruction> Program::getInstructions() const
{
    return instructions;
}

///////////////////////////////////////////////////////////////////////////////
// CORE FUNCTIONALITY
///////////////////////////////////////////////////////////////////////////////

/**
 *  @brief     Execute a Program on the provided feature set.
 *  @details   Upon receiving a feature set, this method will execute each
 *  stored Instruction on the feature set in conjuction with the general
 *  purpose registers held by this Program, then return the first value
 *  in the registers as a bid value.
 *  @param     inputFeatures A double array representing the environment's
 *  complete feature set.
 *  @return    A double value representing a Learner bid.
 *  @todo      Testing required.
 */
double Program::execute(const double* inputFeatures, TpgParameters& parameters)
{
    for (Instruction inst : *instructions) {
        inst.execute(inputFeatures, registers, parameters);
    }

    return registers[0];
}