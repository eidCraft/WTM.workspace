// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class NetworkOptions;
class MutationOptions;
class SelectionOptions;
class SimulationOptions;
class EvaluationOptions;

class EvoController;
class SelectionController;


/**
 * 
 */
class  Options
{
public:
	Options();
	~Options();
};

class  NetworkOptions
{
public:
  int    activityDuration;
  int    relaxationDuration;

  int    maximumLinkLength;

  double addlChargeLeak;
  double addlChargeIncriment;
  double activationThreshold;
  double linkPowerIncrement;
};



class  EvoOptions
{
public:
  friend EvoController;

  EvoOptions();
  void setNeuronsDeletePercent(double);
  void setNeuronsCreatePercent(double);
  void setSynapsesDeletePercent(double);
  void setSynapsesCreatePercent(double);

  void setMutationOutput(int);

  void setSelectionOutput(int);

  void setSimulationEndDelay(int);
  void setTimeLimit(int);
  void setLearningPrecision(int);

private:
  MutationOptions*  mutationOptions;
  SelectionOptions* selectionOptions;

  int timeLimit;
};



class  MutationOptions
{
public:
  double neuronsDeletePercent;
  double neuronsCreatePercent;
  double synapsesDeletePercent;
  double synapsesCreatePercent;

  int mutationOutput;

private:

};



class  SelectionOptions
{
public:
  friend SelectionController;

  SimulationOptions* simulationOptions;
  EvaluationOptions* evaluationOptions;


  int    selectionOutput;
  double learningPrecision;


  SelectionOptions();

};


class  SimulationOptions
{
public:
  int endDelay;

private:

};

class  EvaluationOptions
{
public:
  double tactMatchingThreshold;
  int waitingPeriodLength;

private:

};