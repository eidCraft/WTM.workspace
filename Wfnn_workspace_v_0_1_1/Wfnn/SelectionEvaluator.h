// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Options.h"
#include "TestedAgent.h"
#include "EvaluatedAgent.h"

class SelectionEvaluator;
class IntermediateMarks;
class MatchingPrecedent;
class MatchingPrecedentsSet;

class TestedAgent;
class TestedAgentsGroup;
class EvaluatedAgent;
class EvaluatedAgentsGroup;
class SimulationResult;


/**
 * 
 */
class  SelectionEvaluator
{
public:
	SelectionEvaluator();
	~SelectionEvaluator();

  SelectionEvaluator(EvaluationOptions*);
  EvaluatedAgentsGroup* evaluate(TestedAgentsGroup*);

private:
  EvaluationOptions* options;

  EvaluatedAgent*    evaluateAgent(TestedAgent*);
  double             evaluateResult(SimulationResult*, Scenario*);
  IntermediateMarks* evalueResultsTacts(TestedAgentsGroup*);

  double getMatchingMark(vector<bool> row, vector<bool> pattern);
  double finalEvaluation(vector< vector<double> >);
  //EvaluatedAgentsGroup = finalEvaluation(preliminaryMarks, testedAgents);

};



class  IntermediateMarks
{
public:
  vector< vector<double> > marks;
};



class  MatchingPrecedent
{
public:
  double totalMark;
  //int nextToLastMemberPosition;
  int waitingPosition;
  int lastMemberOutput;

  void   attemptToAddPart(double, int, int);
  void   addPart(double, int, int, int);
  double getDistanceMark(int);

private:

};



class  MatchingPrecedentsSet
{
public:
  vector< vector<MatchingPrecedent*> > precedents;


  void   addMember(double, int, int);
  double getBestMark();
  void   addNewMember(double, int, int);

private:

};
