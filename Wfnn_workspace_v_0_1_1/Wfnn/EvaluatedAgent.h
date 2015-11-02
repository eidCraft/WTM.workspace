// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <vector>

using std::vector;

#include "TestedAgent.h"
#include "SelectionArbiter.h"
#include "SelectionEvaluator.h"

class EvaluatedAgent;
class EvaluatedAgentsGroup;

class TestedAgent;
class EvoAgentsGroup;
class SelectionArbiter;
class SelectionEvaluator;

/**
 * 
 */
class  EvaluatedAgent : public TestedAgent
{
public:
	EvaluatedAgent();
	~EvaluatedAgent();

  friend SelectionEvaluator;
  friend SelectionArbiter;

  EvaluatedAgent(TestedAgent*);
  EvaluatedAgent(EvoAgent*);

  int getMarksAmount();

  void addMark(double);
  vector<double> marks;
  double totalMark;

  double maximumMark;
};



class  EvaluatedAgentsGroup
{
public:
  EvaluatedAgentsGroup();
  EvaluatedAgentsGroup(EvoAgent*);

  void swapAgents(int, int);
  void sortByMark();

  void add(EvaluatedAgent*);
  int  getAgentsAmount();
  int  getMarksAmount();
  size_t size();

  EvoAgentsGroup *reduceToEvoAgents();

  EvaluatedAgent* operator[](int);

  vector<EvaluatedAgent*> agents;

};
