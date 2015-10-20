// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "EvoAgent.h"
#include "Scenario.h"
//#include "SelectionEvaluator.h"


class SimulationResult;
class TestedAgent;
class TestedAgentsGroup;

class SelectionEvaluator;


/**
 *
 */
class  TestedAgent : public EvoAgent
{
public:
  TestedAgent();
  ~TestedAgent();

  friend SelectionEvaluator;

  TestedAgent(ScenariosSet*);
  TestedAgent(EvoAgent*, ScenariosSet*);

  void addResult(SimulationResult*);
  size_t  resultsAmount();

  vector<SimulationResult*>* results;
  ScenariosSet* scenarios;

};

class  SimulationResult
{
public:
  vector< vector<bool> > data;

  void addRow(vector<bool>);
  size_t  length();
};


class  TestedAgentsGroup
{
public:
  TestedAgentsGroup();
  TestedAgentsGroup(TestedAgent*);

  void add(TestedAgent*);
  size_t  agentsAmount();

  TestedAgent* operator[](int);

private:
  vector<TestedAgent*> agents;

};
