#include "tpg_instruction.h"


Instruction::Instruction(TpgParameters& parameters)
{
    // Randomly initialize all of the class variables
    this->mode = static_cast<int8>(floor(parameters.rngUniform() * parameters.modeSize));
    this->source = static_cast<int32>(floor(parameters.rngUniform() * parameters.sourceSize));
    this->destination = static_cast<int8>(floor(parameters.rngUniform() * parameters.learnerRegisterSize));
}

Instruction::Instruction(int8 mode, int32 source, int8 destination)
{
    this->mode = mode;
    this->source = source;
    this->destination = destination;
}

Instruction::~Instruction()
{

}