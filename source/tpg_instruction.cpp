#include "tpg_instruction.h"

#include <string>

#include "tpg_utility.h"
#include "tpg_operation.h"
#include "tpg_operations_list.h"

Instruction::Instruction(TpgParameters& parameters)
{
    // Randomly initialize all of the class variables
    this->mode = static_cast<int8>(
        floor(parameters.rngUniform() * parameters.modeSize)
    );
    
    this->source = static_cast<int32>(
        floor(parameters.rngUniform() * parameters.sourceSize)
    );

    this->destination = static_cast<int8>(
        floor(parameters.rngUniform() * parameters.learnerRegisterSize)
    );
    
    this->operation = &(Instruction::createOperationOfType(
        static_cast<int8>(
            floor(parameters.rngUniform() * parameters.numberOfOperations)
        )
    ));
}

Instruction::Instruction(int8 mode, int32 source, int8 destination, 
    Operation* operation)
{
    // TODO: (Robert) The operation should be making a copy of the
    //       incoming operation.
    this->mode = mode;
    this->source = source;
    this->destination = destination;
    this->operation = operation;
}

Instruction::Instruction(Instruction* other)
{
    this->mode = other->mode;
    this->source = other->source;
    this->destination = other->destination;
    this->operation = other->operation;
}

Instruction::~Instruction()
{

}

bool Instruction::execute(const double* inputFeatures, 
        double* registers,
        TpgParameters& parameters) const
{
    return this->operation->execute(this->mode,
        this->source,
        this->destination,
        inputFeatures,
        registers,
        parameters);
}

bool Instruction::mutate(TpgParameters& parameters)
{
    return true;
}

std::string Instruction::getType() const
{
    return this->operation->toString();
}

std::string Instruction::toString() const
{
    return this->operation->toString() + " "
        + std::to_string(this->mode) + " "
        + std::to_string(this->source) + " "
        + std::to_string(this->destination);
}

std::string Instruction::toStorage() const
{
    return this->toString();
}

Operation& Instruction::createOperationOfType(const Operations& type)
{
    // Create a pointer for holding an operation
    Operation* operation = nullptr;

    // Switch through the types to generate the proper
    // operation and return it. 
    // TODO: (Robert) Investigate whether or not this
    //       is possible using a pointer to one existing
    //       operation object. It should be!
    switch(type)
    {
        case Operations::Add:
            operation = new AddOperation();
            break;
        case Operations::Subtract:
            operation = new SubtractOperation();
            break;
        case Operations::Multiply:
            operation = new MultiplyOperation();
            break;
        case Operations::Divide:
            operation = new DivideOperation();
            break;
        case Operations::Cosine:
            operation = new CosineOperation();
            break;
        case Operations::Exp:
            operation = new ExpOperation();
            break;
        case Operations::Logarithm:
            operation = new LogarithmOperation();
            break;
        case Operations::Conditional:
            operation = new ConditionalOperation();
            break;
        case Operations::MemWrite:
            operation = new MemWriteOperation();
    }

    // Return the operation. This will be an outgoing reference.
    // This will crash the program if no valid operation was found.
    return *(operation);
}

Operation& Instruction::createOperationOfType(int8 type)
{
    return Instruction::createOperationOfType(static_cast<Operations>(type));
}