#ifndef TPG_UNIVERSAL_TPGPROGRAM_H_
#define TPG_UNIVERSAL_TPGPROGRAM_H_

#include "tpg_utility.h"

#include <map>
#include <string>
#include <vector>

#include "tpg_instruction.h"

/**
 *  @brief     A class which represents a program using a collection of
 *  Instruction objects.
 *  @details   The Program class contains a list of Instruction objects which 
 *  represent register-based instructions, closely resembling assembly code.
 *  A Program contains a set of general purpose registers which act as local
 *  memory. These registers may retain their state between executions or not,
 *  where doing so can result in persistent local memory for "remembering"
 *  past decisions. <br><br>When a Program is executed, it iterates through
 *  its Instruction list and executes them one at a time, allowing them access
 *  to the general purpose registers. When the process is completed and the 
 *  general purpose registers have been populated, the value held in the first
 *  general purpose register is available as a bid value for the Learner which
 *  executed a given Program.
 *  @author    Robert Smith
 *  @author    Other
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 7, 2019.
 *  @pre       Initialize the TPGAlgorithm object, which generates a TPGLearn
    or TPGPlay objects and creates a population of Learners for producing bids.
 *  @bug       None yet marked.
 *  @todo      Implementation and full commenting required.
 *  @copyright Not Yet Decided.
 */
class Program
{
    /**A vector of Instruction objects which represent a complete TPG program.*/
    std::vector<Instruction> instructions;
    /**A double array which acts as a set of general purpose registers.*/
    double* registers;
    /**A 32-bit integer which sets a limit on the maximum size of a Program.*/
    int32 maximumProgramSize;

public:
    Program(TpgParameters*);
    Program(Program*);
    double execute(double*);
    bool mutate(TpgParameters*);
    int32 instructionCount(std::string*);
    std::map<std::string, int32>* allInstructionCounts(TpgParameters*);
    std::string* toString();
};

#endif