#ifndef TPG_UNIVERSAL_TPGINSTRUCTION_H_
#define TPG_UNIVERSAL_TPGINSTRUCTION_H_

#include "tpg_utility.h"

#include <functional>
#include <string>

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