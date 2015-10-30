// Fill out your copyright notice in the Description page of Project Settings.


#include "GenomManager.h"

GenomManager::GenomManager()
{
}

GenomManager::~GenomManager()
{
}


#include <fstream>
#include <iostream>
#include <sstream> 

using std::ifstream;
using std::cout;
using std::endl;

#include "GenomManager.h"
#include "Genom.h"


Genom*
GenomManager::loadGenom(std::string filename)
{
  Genom* destGenom = new Genom();

  ifstream source(filename);

  string skip;
  source >> skip;

  loadName(source, destGenom);
  loadOptions(source, destGenom);
  loadNeurons(source, destGenom);
  loadSynapses(source, destGenom);
  loadInputs(source, destGenom);
  loadOutputs(source, destGenom);

  return destGenom;
}

void
GenomManager::loadName(ifstream& source, Genom* genom)
{
  separateAndDissolveValues(source, genom, &GenomManager::nameFill);
}


void
GenomManager::loadOptions(ifstream& source, Genom* genom)
{
  separateAndDissolveValues(source, genom, &GenomManager::yieldOptionsFill);
}


void
GenomManager::loadNeurons(ifstream& source, Genom* genom)
{
  separateAndDissolveValues(source, genom, &GenomManager::yieldNeuronsFill);

  size_t maxId = 0;

  for (int neuronId : genom->neurons)
  {
    if (neuronId > maxId) maxId = neuronId;
  }

  genom->maxNeuronId = maxId;
}

void
GenomManager::loadSynapses(ifstream& source, Genom* genom)
{
  separateAndDissolveValues(source, genom, &GenomManager::yieldSynapsesFill);
}



void
GenomManager::separateAndDissolveValues(
ifstream& fin, Genom* genom,
void (GenomManager::*f)(Genom*, string))
{
  string entireString;
  string part;

  fin >> entireString;

  std::size_t found = entireString.find(";");

  bool isFound = (found != std::string::npos);
  if (isFound)
  {
    part = entireString.substr(0, found);

    entireString = entireString.substr(found + 1,
      entireString.size() - found);

    while (!part.empty())
    {
      (this->*f)(genom, part);

      found = entireString.find(";");
      part = entireString.substr(0, found);

      entireString = entireString.substr(found + 1,
        entireString.size() - found);
    }
  }
  else
  {
    std::cout << "Can't find separator. Incorrect data." << std::endl;
    exit(1);
  }
}


void
GenomManager::nameFill(
  Genom* genom, string value)
{
  genom->name = value;
}


void
GenomManager::yieldOptionsFill(
  Genom* genom, string value)
{
  static int progressIndex;

  switch (progressIndex)
  {
  case 0:
    genom->options->activationThreshold = stod(value);
    break;
  case 1:
    genom->options->activityDuration = stoi(value);
    break;
  case 2:
    genom->options->relaxationDuration = stoi(value);
    break;
  case 3:
    genom->options->addlChargeLeak = stod(value);
    break;
  case 4:
    genom->options->addlChargeIncriment = stod(value);
    break;
  case 5:
    genom->options->linkPowerIncrement = stod(value);
    break;
  case 6:
    genom->options->maximumLinkLength = stoi(value);
    break;
  default:
    cout << "Index is out of NetworkParameters" << endl;
    break;
  }
  progressIndex++;
}


void
GenomManager::yieldNeuronsFill(Genom* genom, string neuronId)
{
  genom->neurons.emplace_back(std::stoi(neuronId));
}


void
GenomManager::yieldSynapsesFill(Genom* genom, string synapsePart)
{
  static int yieldProgressIndex;
  static StoredSynapse* lastSynapse;

  switch (yieldProgressIndex)
  {
  case 0:
  {
    int id = stoi(synapsePart);

    lastSynapse = new StoredSynapse();

    lastSynapse->presynapticNeuron = id;

    genom->synapses.emplace_back(lastSynapse);
  }
  break;

  case 1:
  {
    int id = stoi(synapsePart);

    lastSynapse->postsynapticNeuron = id;
  }
  break;

  case 2:
  {
    double length = stod(synapsePart);

    lastSynapse->length = length;
  }
  break;

  case 3:
  {
    double weigth = stod(synapsePart);

    lastSynapse->weigth = weigth;
  }
  break;

  default:
  {
    cout << "Out of yieldProgessIndex. Do something." << endl;
  }
  break;
  }

  bool isEndOfSynapsDescription = (yieldProgressIndex == 3);
  if (isEndOfSynapsDescription)
  {
    yieldProgressIndex = 0;
  }
  else
  {
    yieldProgressIndex++;
  }
}







void
GenomManager::loadInputs(ifstream& source, Genom* genom)
{
  separateAndDissolveValues(source, genom, &GenomManager::yieldInputsFill);
}


void
GenomManager::loadOutputs(ifstream& source, Genom* genom)
{
  separateAndDissolveValues(source, genom, &GenomManager::yieldOutputsFill);
}








void
GenomManager::yieldInputsFill(
Genom* genom, string value)
{
  int id = stod(value);
  genom->inputNeurons.emplace_back(id);
}



void
GenomManager::yieldOutputsFill(
Genom* genom, string value)
{
  int id = stod(value);
  genom->outputNeurons.emplace_back(id);
}



