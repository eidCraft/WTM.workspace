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
  EvaluatedAgentsGroup* initialAgents, ScenariosSet* scenarios)
{
  TestedAgentsGroup* testedAgents = simController->makeSimulations(
    scenarios, initialAgents);

  EvaluatedAgentsGroup* evaluatedAgents = selectionEvaluator->evaluate(
    testedAgents);

  EvaluatedAgentsGroup* selectedAgents = selectionArbiter->select(
    evaluatedAgents, options->selectionOutput);

  learningGoalExcited = learningGoalChecking(selectedAgents);

  return selectedAgents;
}


bool
SelectionController::isLearningGoalExcited()
{
  return learningGoalExcited;
}


// Need to calculate maximum mark for each scenarion and maximum mark for scenarios set
bool
SelectionController::learningGoalChecking(EvaluatedAgentsGroup* agentsGroup)
{
  bool excited = false;

//  size_t nAgents = agentsGroup->agents.size();
  //for (size_t iAgent = 0; iAgent != nAgents; iAgent++)
  //{
//  double evolutionEndPercentThreshold =
//      options->evolutionAccurancy * agentsGroup->agents.at(0);

    //agentsGroup->agents.at(0)->totalMark >= ;
  //}
  return excited;
}
