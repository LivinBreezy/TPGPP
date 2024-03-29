#ifndef TPG_UNIVERSAL_TPGINSTRUCTION_H_
#define TPG_UNIVERSAL_TPGINSTRUCTION_H_

#include "tpg_utility.h"

#include <string>

#include "tpg_operation.h"

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
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 12, 2019.
 *  @pre       When Learners are initialized, they will be given a Program
 *  which generates and holds Instructions.
 *  @bug       None yet marked.
 *  @todo      Implementation and full commenting required.
 *  @copyright Not Yet Decided.
 */
class Instruction
{
public:
    Instruction(TpgParameters&);
    Instruction(int8, int32, int8, Operation*);
    Instruction(Instruction*);
    ~Instruction();
    bool execute(const double*, double*, TpgParameters&) const;
    int8 getMode() const;
    int32 getSource() const;
    int8 getDestination() const;
    Operation* getOperation() const;
    std::string getType() const;
    std::string toString() const;
    std::string toStorage() const;
    static Operation& createOperationOfType(const Operations&);
    static Operation& createOperationOfType(int8);

protected:
    int8 mode;
    int32 source;
    int8 destination;
    Operation* operation;
};

#endif