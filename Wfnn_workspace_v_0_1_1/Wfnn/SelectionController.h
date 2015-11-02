// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Options.h"
#include "EvoAgent.h"
#include "Scenario.h"
#include "EvaluatedAgent.h"
#include "SimulationController.h"
#include "SelectionEvaluator.h"
#include "SelectionArbiter.h"


/**
 * 
 */
class  SelectionController
{
public:
	SelectionController();
	~SelectionController();

  SelectionController(SelectionOptions*);

  EvaluatedAgentsGroup* selectAgents(EvaluatedAgentsGroup *, ScenariosSet*);

  bool isLearningGoalExcited();

private:
  SelectionOptions*     options;
  SimulationController* simController;
  SelectionEvaluator*   selectionEvaluator;
  SelectionArbiter*     selectionArbiter;

  bool learningGoalExcited = false;

  bool learningGoalChecking(EvaluatedAgentsGroup*);

};
