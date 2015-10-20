#include "ScenarioManager.h"

#include <fstream>
#include <iostream>


ScenarioManager::ScenarioManager()
{
}

ScenarioManager::~ScenarioManager()
{
}








Scenario*
ScenarioManager::loadFromFile(std::string filename)
{
  std::ifstream dataStream(filename);

  bool isFileValid = compatibilityCheck(dataStream);
  if (isFileValid == true)
  {
    Scenario* scenario = uploadScenario(dataStream);

    dataStream.close();
    return scenario;
  }

  std::cout << "Data file is not valid." << std::endl;
  dataStream.close();
  //GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString("Scenario file is not valid."));

  return nullptr;
}


bool
ScenarioManager::compatibilityCheck(std::ifstream& dataStream)
{
  std::string identificator;

  dataStream >> identificator;

  bool isDataCompetable = (identificator == string("WfnnSimulationScenario"));

  return isDataCompetable;
}



Scenario*
ScenarioManager::uploadScenario(std::ifstream& dataStream)
{
  string data;
  Scenario* scenario = new Scenario();


  dataStream >> data;
  scenario->networkName = data;

  dataStream >> data;
  scenario->simulationName = data;

  dataStream >> data;
  loadInputData(scenario, data);

  dataStream >> data;
  loadOutputData(scenario, data);

  scenario->simulationDuration = scenario->inputData.size();

  scenario->useIndex = 0;

  return scenario;
}


void
ScenarioManager::loadAmounts(Scenario* scenario, string data)
{

  std::size_t delimiter = data.find(";");
  std::size_t endOfData = data.size() - delimiter - 1;

  bool isFound = (delimiter != std::string::npos);
  if (isFound)
  {
    scenario->inputsAmount = stoi(data.substr(0, delimiter));
    scenario->outputsAmount = stoi(data.substr(delimiter + 1, endOfData));
  }
  else
  {
    std::cout << "Data is empty. Do something!" << std::endl;
  }
}



void
ScenarioManager::separateAndDissolveValues(
Scenario* scenario, string data,
void (ScenarioManager::*f)(Scenario*, string))
{
  string entireString = data;
  string part;

  std::size_t found = entireString.find(";");

  bool isFound = (found != std::string::npos);
  if (isFound)
  {
    part = entireString.substr(0, found);

    entireString = entireString.substr(found + 1,
      entireString.size() - found);

    while (!part.empty())
    {
      (this->*f)(scenario, part);

      found = entireString.find(";");
      part = entireString.substr(0, found);

      entireString = entireString.substr(found + 1,
        entireString.size() - found);
    }
  }
  else
  {
    std::cout << "Can't find separator. Incorrect data." << std::endl;
    //GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString("Can't find separator. Incorrect data."));
  }
}



void
ScenarioManager::loadInputData(Scenario* scenario, string data)
{
  separateAndDissolveValues(scenario, data,
    &ScenarioManager::yieledInputDataLoad);
}

void
ScenarioManager::loadOutputData(Scenario* scenario, string data)
{
  separateAndDissolveValues(scenario, data,
    &ScenarioManager::yieledOutputDataLoad);
}


// если здесь будет жаловаться, то добавить emplace_back
void
ScenarioManager::yieledInputDataLoad(Scenario* scenario, string data)
{
  int valuesAmount = data.size();

  vector<bool> row(valuesAmount);

  for (size_t i = 0; i < valuesAmount; i++)
  {
    row.at(i) = (data.at(i) == '1');
  }

  scenario->inputData.emplace_back(row);
}


void
ScenarioManager::yieledOutputDataLoad(Scenario* scenario, string data)
{
  int valuesAmount = data.size();

  vector<bool> row(valuesAmount);

  for (size_t i = 0; i < valuesAmount; i++)
  {
    row.at(i) = (data.at(i) == '1');
  }

  scenario->outputData.emplace_back(row);
}
