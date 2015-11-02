// Fill out your copyright notice in the Description page of Project Settings.


#include "Scenario.h"

#include <iostream>

Scenario::Scenario()
{
}

Scenario::~Scenario()
{
}


ScenariosSet::ScenariosSet()
{
  maximumMark = 0;
}


void
ScenariosSet::add(Scenario* scenario)
{
  if (scenario != nullptr)
  {
    scenarios.emplace_back(scenario);

    maximumMark += scenario->outputData.size()  * scenario->outputsAmount;
  }
  else
  {
    std::cout << "ScenarioSet. Adding an empty scenario.";
    exit(1);
  }
}


int
ScenariosSet::size()
{
  return scenarios.size();
}


Scenario*
ScenariosSet::operator[](int index)
{
  return scenarios[index];
}
