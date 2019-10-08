#ifndef TPG_UNIVERSAL_TPGINSTRUCTION_H_
#define TPG_UNIVERSAL_TPGINSTRUCTION_H_

#include "tpg_utility.h"

#include <functional>
#include <string>

/**
 *  @brief     Represents a register-based instruction similar to assembly.
 *  @details   The Instruction class contains a variety of information as it
 *  pertains to register-based instructions. It holds a mode value (for
 *  determining the type of source to read from), a source index value (for
 *  determining which index of the given source structure to read from), and
 *  a destination index value (for determining the other value to operate on
 *  as well as where to store the result). The class also holds a function
 *  which represents the functionality of the defined operation.
 *  @author    Robert Smith
 *  @author    Other
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 7, 2019.
 *  @pre       When Learners are initialized, they will be given a Program
 *  which generates and holds Instructions.
 *  @bug       None yet marked.
 *  @todo      Implementation and full commenting required.
 *  @copyright Not Yet Decided.
 */
class Instruction
{
    int8 mode;
    int32 source;
    int8 destination;
    std::function<bool(int8, int32, int8, double*, double*, TpgParameters*)> operation;

public:
    Instruction(int8, int32, int8, std::function<double*(int8, int32, int8, double*, double*, TpgParameters*)>);
    bool execute(double*, double*, TpgParameters*);
    bool mutate(TpgParameters*);
    std::string* toString();
};

#endif

/*
Instruction
    Class Variables
        mode : int8
        source : int32
        destination : int8
        operation : F*
    Methods
        Instruction : int8, string, int32, int8, struct (parameters)
        execute : double[], double[], struct (parameters/memory)
        mutate : struct (mutation parameters)
        toString : None

    Static Methods
        generateOperations : None
*/