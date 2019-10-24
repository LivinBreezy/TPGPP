
#include "tpg_program.h"

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
Program::Program(const Program& other)
{
    this->instructions = {};
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

    for (Instruction inst : *instructions) {
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
 *  @todo      Implementation and full commenting required. Implement later
 *  once Instruction is finalized.
 */
std::unordered_map<std::string, int64>& Program::allInstructionCounts(const TpgParameters& parameters) const
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
        instTypes.emplace(inst.getType);
    }

    // find counts
    for (Instruction inst : *instructions) 
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

std::vector<Instruction>* Program::getInstructions() const
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

/**
 *  @brief     Mutate the Instructions in a Program.
 *  @details   Uses the given parameters to mutate this Program object.
 *  This includes inserting, deleting, or mutating some instruction(s), or
 *  swapping two instructions locations.
 *  @param     parameters A struct held by the main TPG algorithm objects
 *  (TpgLearn or TpgPlay) and stores all of the current parameter values
 *  for the current environment.
 *  @return    A boolean value which is true if Instructions were mutated.
 *  Otherwise return false.
 *  @todo      Testing required.
 */
bool Program::mutate(TpgParameters& parameters)
{
    bool changed = false;

    // delete instruction
    if (instructions->size() > 1 && 
            parameters.rngFlip(parameters.probInstructionDelete)) 
    {
        instructions->erase(instructions->begin() + parameters.rngInt64(0, instructions->size()));
        changed = true;
    }

    // insert a new random instruction
    if (instructions->size() < parameters.maximumProgramSize && 
            parameters.rngFlip(parameters.probInstructionDelete)) 
    {
        instructions->insert(instructions->begin() + parameters.rngInt64(0, instructions->size()), 
                             Instruction(parameters));
        changed = true;
    }

    // mutate an instruction
    if (parameters.rngFlip(parameters.probInstructionMutate)) 
    {
        instructions->at(parameters.rngInt64(0, instructions->size())).mutate(parameters);
        changed = true;
    }

    // swap 2 instruction
    if (instructions->size() > 1 && parameters.rngFlip(parameters.probInstructionSwap))
    {
        // ensure different indices
        int64 index1 = parameters.rngInt64(0, instructions->size());
        int64 index2 = parameters.rngInt64(0, instructions->size());
        while (index1 == index2)
        {
            index2 = parameters.rngInt64(0, instructions->size()); 
        }

        Instruction tmpInst = instructions->at(index1);
        instructions->at(index1) = instructions->at(index2);
        instructions->at(index2) = tmpInst;
        changed = true;
    }

    return changed;
}

///////////////////////////////////////////////////////////////////////////////
// UTILITY
///////////////////////////////////////////////////////////////////////////////

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