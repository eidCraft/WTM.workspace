// Fill out your copyright notice in the Description page of Project Settings.


#include "TestedAgent.h"

TestedAgent::TestedAgent()
{
  results = new vector<SimulationResult*>();
}

TestedAgent::~TestedAgent()
{
  results = new vector<SimulationResult*>();
}


TestedAgent::TestedAgent(ScenariosSet* scenarios)
{
  this->scenarios = scenarios;
  results = new vector<SimulationResult*>();
}

void
TestedAgent::addResult(SimulationResult* result)
{
  results->emplace_back(result);
}

size_t TestedAgent::resultsAmount()
{
  return results->size();
}


size_t
SimulationResult::length()
{
  return data.size();
}

void
SimulationResult::addRow(vector<bool> row)
{
  data.emplace_back(row);
}

TestedAgentsGroup::TestedAgentsGroup(){}

void
TestedAgentsGroup::add(TestedAgent* testedAgent)
{
  agents.emplace_back(testedAgent);
}


size_t
TestedAgentsGroup::agentsAmount()
{
  return agents.size();
}

TestedAgent*
TestedAgentsGroup::operator [](int index)
{
  return agents[index];
}

TestedAgent::TestedAgent(EvoAgent* baseAgent, ScenariosSet* scenariosSet)
{
  this->genom   = baseAgent->genom;
  this->network = baseAgent->network;

  this->scenarios = scenariosSet;

  this->results = new vector<SimulationResult*>();
}


