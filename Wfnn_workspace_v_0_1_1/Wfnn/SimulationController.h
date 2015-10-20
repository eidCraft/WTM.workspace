// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EvoAgent.h"
#include "Scenario.h"
#include "TestedAgent.h"


/**
 * 
 */
class  SimulationController
{
public:
	SimulationController();
	~SimulationController();

  SimulationController(SimulationOptions*);
  TestedAgentsGroup* makeSimulations(ScenariosSet*, EvoAgentsGroup*);

private:
  SimulationOptions* options;

  bool compatibilityCheck(ScenariosSet*, EvoAgentsGroup*);
  SimulationResult* simulate(Scenario*, EvoAgent*);

  void setInputDataSequentially(Scenario*, Network*);

};
