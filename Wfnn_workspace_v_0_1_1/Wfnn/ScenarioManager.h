// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include <fstream>

#include "Scenario.h"

/**
 *
 */
class  ScenarioManager
{
public:
  ScenarioManager();
  ~ScenarioManager();

  Scenario* loadFromFile(std::string);

private:
  bool compatibilityCheck(std::ifstream&);

  Scenario* uploadScenario(std::ifstream&);

  void loadAmounts(Scenario*, string);
  void loadInputData(Scenario*, string);
  void loadOutputData(Scenario*, string);

  void separateAndDissolveValues(
    Scenario* scenario, string data,
    void (ScenarioManager::*f)(Scenario*, string));

  void yieledInputDataLoad(Scenario*, string);
  void yieledOutputDataLoad(Scenario*, string);

};
