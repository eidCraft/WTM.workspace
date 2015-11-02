// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EvoAgent.h"
#include "Scenario.h"
#include "TestedAgent.h"
#include "EvaluatedAgent.h"

/**
 * 
 */
class  SimulationController
{
public:
	SimulationController();
	~SimulationController();

  SimulationController(SimulationOptions*);
  TestedAgentsGroup* makeSimulations(ScenariosSet*, EvaluatedAgentsGroup *);

private:
  SimulationOptions* options;

  bool compatibilityCheck(ScenariosSet*, EvaluatedAgentsGroup*);
  SimulationResult* simulate(Scenario*, EvaluatedAgent *);

  void setInputDataSequentially(Scenario*, Network*);

};
