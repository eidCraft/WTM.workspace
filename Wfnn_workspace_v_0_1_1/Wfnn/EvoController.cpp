// Fill out your copyright notice in the Description page of Project Settings.


#include "EvoController.h"

EvoController::EvoController()
{
}

EvoController::~EvoController()
{
}


EvoController::EvoController(EvoOptions* evoOptions)
{
  mutationController = new MutationController(
    evoOptions->mutationOptions);

  selectionController = new SelectionController(
    evoOptions->selectionOptions);
}



void
EvoController::startTimer()
{
  beginTime = std::time(nullptr);
}


bool
EvoController::isTimeLimitExcited()
{
  std::time_t now = std::time(nullptr);

  bool   isExcited = (now >= beginTime + options->timeLimit);
  return isExcited;
}


EvaluatedAgentsGroup*
EvoController::evolve(EvoAgent* agent, ScenariosSet* scenarios)
{
  EvoAgentsGroup*       currentAgents = new EvoAgentsGroup(agent);
  EvaluatedAgentsGroup* evaluedAgents;

  startTimer();

  bool stopEvo;
  while (true)
  {
    currentAgents = mutationController->mutateAgents(currentAgents);

    evaluedAgents = selectionController->selectAgents(
      currentAgents, scenarios);

    stopEvo = (selectionController->isLearningGoalExcited() ||
      isTimeLimitExcited());

    if (stopEvo) break;
  }

  return evaluedAgents->reduceToEvoAgents();
}




