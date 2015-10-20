// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <ctime>

#include "Options.h"
#include "EvoAgent.h"

#include "Scenario.h"

#include "MutationController.h"
#include "SelectionController.h"


/**
 * 
 */
class  EvoController
{
public:
	EvoController();
	~EvoController();

  EvoController(EvoOptions*);

  EvaluatedAgentsGroup* evolve(EvoAgent*, ScenariosSet*);

private:
  EvoOptions* options;

  MutationController*  mutationController;
  SelectionController* selectionController;

  std::time_t beginTime;


  void startTimer();
  bool isTimeLimitExcited();

};
