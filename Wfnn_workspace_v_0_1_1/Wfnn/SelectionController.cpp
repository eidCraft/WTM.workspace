// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionController.h"

SelectionController::SelectionController()
{
}

SelectionController::~SelectionController()
{
}


SelectionController::SelectionController(SelectionOptions* options)
{
  this->options = options;

  simController = new SimulationController(options->simulationOptions);

  selectionEvaluator = new SelectionEvaluator(options->evaluationOptions);

  selectionArbiter = new SelectionArbiter();

}




EvaluatedAgentsGroup*
SelectionController::selectAgents(
  EvoAgentsGroup* initialAgents, ScenariosSet* scenarios)
{
  TestedAgentsGroup* testedAgents = simController->makeSimulations(
    scenarios, initialAgents);

  EvaluatedAgentsGroup* evaluatedAgents = selectionEvaluator->evaluate(
    testedAgents);

  EvaluatedAgentsGroup* selectedAgents = selectionArbiter->select(
    evaluatedAgents);

  learningGoalExcited = learningGoalChecking(selectedAgents);

  return selectedAgents;
}


bool
SelectionController::isLearningGoalExcited()
{
  bool isExcited = true;




  return isExcited;
}


bool
SelectionController::learningGoalChecking(EvaluatedAgentsGroup* agents)
{
  bool excited = true;

  return excited;
}
