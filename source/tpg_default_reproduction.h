#ifndef TPG_UNIVERSAL_TPGDEFAULTREPRODUCTION_H_
#define TPG_UNIVERSAL_TPGDEFAULTREPRODUCTION_H_

#include "tpg_utility.h"

#include <vector>

#include "tpg_reproduction.h"
#include "tpg_team.h"
#include "tpg_learner.h"
#include "tpg_action.h"
#include "tpg_program.h"
#include "tpg_instruction.h"

/**
 *  @brief     Base abstract class used for defining a reproductive class.
 *  @details   The Reproduction class is a fully abstract (pure virtual) class
 *  which defines the four required methods for creating a reproductive class
 *  in TPG. The methods are designed to be used in tandem as to:
 *  -# Use teamSelection to return a list of the best ranked Teams.
 *  -# Use teamReproduction to produce the children of the best ranked Teams.
 *  -# Use teamMutation to mutate those children.
 *  -# Use teamUnify to combine the best parents and their children into a
 *  single Team population.
 *  @author    Robert Smith
 *  @author    Other
 *  @version   v0.1 Beta
 *  @date      Created on October 7, 2019. Last updated on October 7, 2019.
 *  @pre       Initialize the TPGAlgorithm object, which generates a TPGLearn
    or TPGPlay objects.
 *  @bug       None yet marked.
 *  @todo      Create the following reproduction classes/styles:
 *  -# Regular Crossover/Mutation (StandardReproduction class)
 *  -# Regular Crossover Only (StandardCrossover class)
 *  -# Regular Mutation Only (StandardMutation class)
 *  -# Stephen's Crossover/Mutation (StephenReproduction class)
 *  @copyright Not Yet Decided.
 */
class StandardReproduction : public Reproduction
{
  public:
    std::vector<Team*> teamSelection(std::vector<Team*>&, TpgParameters&);
    std::vector<Team*> teamReproduction(std::vector<Team*>&, TpgParameters&);
    std::vector<Team*> teamMutation(std::vector<Team*>&, TpgParameters&);

  private:
    Program mutateProgram(Program&, TpgParameters&);
    Instruction mutateInstruction(Instruction&, TpgParameters&);
    Action mutateAction(Action&, TpgParameters&);
};

#endif