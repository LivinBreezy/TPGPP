#ifndef TPG_UNIVERSAL_TPGPROGRAM_H_
#define TPG_UNIVERSAL_TPGPROGRAM_H_

#include "tpg_utility.h"

#include <unordered_map>
#include <string>
#include <string_view>
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
 *  @author    Ryan Amaral 
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 25, 2019.
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
    std::vector<double> registers;

  public:
    // constructors and destructor
    Program(TpgParameters&);
    Program(const Program&, TpgParameters&);
    ~Program();

    // getters and setters
    int64 instructionCount(const std::string_view&) const;
    std::unordered_map<std::string, int64> allInstructionCounts(const TpgParameters&) const;
    std::vector<Instruction> getInstructions() const;

    // core functionality
    double execute(const double*, TpgParameters&);
  
    std::string* toString() const;
};

#endif