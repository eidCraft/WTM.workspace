// Fill out your copyright notice in the Description page of Project Settings.

#include "SimulationController.h"

SimulationController::SimulationController()
{
}

SimulationController::~SimulationController()
{
}




#include <iostream>

#include "SimulationController.h"



SimulationController::SimulationController(SimulationOptions* options)
{
  this->options = options;
}



TestedAgentsGroup*
SimulationController::makeSimulations(
ScenariosSet* scenarios, EvoAgentsGroup* agents)
{
  bool  isAllObjectCompetable = compatibilityCheck(scenarios, agents);
  if (!isAllObjectCompetable)
  {
    std::cout << "Networks and simulations are not compatible." <<
      "Look where you wrong" << std::endl;
    exit(1);
  }

  TestedAgentsGroup* testedAgents = new TestedAgentsGroup();
  TestedAgent*       currentAgent;
  SimulationResult*  currentResult;

  int agentsAmount = agents->size();
  int simulationsAmount = scenarios->size();

  for (int i = 0; i < agentsAmount; i++)
  {
    currentAgent = new TestedAgent((*agents)[i], scenarios);

    for (int j = 0; j < simulationsAmount; j++)
    {
      currentResult = simulate((*scenarios)[j], (*agents)[i]);

      currentAgent->addResult(currentResult);
    }
    testedAgents->add(currentAgent);
  }
  return testedAgents;
}



SimulationResult*
SimulationController::simulate(
Scenario* scenario, EvoAgent* agent)
{
  SimulationResult* result = new SimulationResult();

  int totalSimulationLength =
    scenario->simulationDuration + options->endDelay;

  for (int k = 0; k < totalSimulationLength; k++)
  {
    setInputDataSequentially(scenario, agent->network);

    agent->network->makeSimulationTact();

    result->addRow(agent->network->getOutputs());
  }
  return result;
}



void
SimulationController::setInputDataSequentially(
Scenario* scenario, Network* network)
{
  bool isDataStillRemained = (scenario->useIndex < scenario->simulationDuration);
  if (isDataStillRemained)
  {
    network->setInputValues(scenario->inputData[scenario->useIndex]);
    scenario->useIndex++;
  }
}



bool
SimulationController::compatibilityCheck(
ScenariosSet* scenarios, EvoAgentsGroup* agents)
{
  bool isDataCompatible = true;
  bool localCompatibility = true;

  int agentsAmount = agents->size();
  int simulationsAmount = scenarios->size();

  for (int i = 0; i < agentsAmount; i++)
  {
    for (int j = 0; j < simulationsAmount; j++)
    {
      localCompatibility = ((*agents)[i]->network->name ==
        (*scenarios)[j]->networkName);

      if (!localCompatibility)
      {
        isDataCompatible = false;
        goto endOfLoops;
      }
    }
  }
endOfLoops:

  return isDataCompatible;
}


