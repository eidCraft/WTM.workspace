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

  int getMarksAmount();

  void addMark(double);
  vector<double> marks;

};



class  EvaluatedAgentsGroup
{
public:
  EvaluatedAgentsGroup();
  EvaluatedAgentsGroup(EvaluatedAgent*);

  void add(EvaluatedAgent*);
  int  getAgentsAmount();
  int  getMarksAmount();

  EvaluatedAgentsGroup* reduceToEvoAgents();

  EvaluatedAgent* operator[](int);

  vector<EvaluatedAgent*> agents;

};
