// Fill out your copyright notice in the Description page of Project Settings.


#include "EvoController.h"

#include "iostream"

EvoController::EvoController()
{
  iCurrentEpoch = 0;
}

EvoController::~EvoController()
{
}


EvoController::EvoController(EvoOptions* evoOptions)
{
  this->options = evoOptions;

  mutationController = new MutationController(
    evoOptions->mutationOptions);

  selectionController = new SelectionController(
    evoOptions->selectionOptions);

  iCurrentEpoch = 0;
}

bool
EvoController::isEpochsLimitExcited()
{
  bool   isExcited = ++iCurrentEpoch >= options->epochsLimit;
  return isExcited;
}


EvaluatedAgentsGroup*
EvoController::evolve(EvoAgent* agent, ScenariosSet* scenarios)
{
  EvaluatedAgentsGroup* currentAgents = new EvaluatedAgentsGroup(agent);

  bool stopEvo;
  while (true)
  {
    currentAgents = mutationController->mutateAgents(currentAgents);

    currentAgents = selectionController->selectAgents(
      currentAgents, scenarios);

    stopEvo = selectionController->isLearningGoalExcited();
    stopEvo = stopEvo || isEpochsLimitExcited();

    if (stopEvo) break;
  }
  return currentAgents;
}




