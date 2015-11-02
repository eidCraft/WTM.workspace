// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

class Scenario;
class ScenariosSet;

/**
 *
 */
class  Scenario
{
public:
  Scenario();
  ~Scenario();

  string networkName;
  string simulationName;

  vector< vector<bool> > inputData;
  vector< vector<bool> > outputData;

  int inputsAmount;
  int outputsAmount;
  int simulationDuration;

  int useIndex;
private:

};


class  ScenariosSet
{
public:
  ScenariosSet();
  void add(Scenario*);
  int  size();

  Scenario* operator[](int);


  vector<Scenario*> scenarios;

  double maximumMark;

};
