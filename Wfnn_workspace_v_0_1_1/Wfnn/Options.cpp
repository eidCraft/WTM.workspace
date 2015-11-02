

#include "Options.h"


EvoOptions::EvoOptions()
{
  mutationOptions  = new MutationOptions();
  selectionOptions = new SelectionOptions();
}

SelectionOptions::SelectionOptions()
{
  simulationOptions  = new SimulationOptions();
}

void
EvoOptions::setNeuronsDeletePercent(double percent)
{
  this->mutationOptions->neuronsDeletePercent = percent;
}


void
EvoOptions::setNeuronsCreatePercent(double percent)
{
  this->mutationOptions->neuronsCreatePercent = percent;
}


void
EvoOptions::setSynapsesDeletePercent(double percent)
{
  this->mutationOptions->synapsesDeletePercent = percent;
}


void
EvoOptions::setSynapsesCreatePercent(double percent)
{
  this->mutationOptions->synapsesCreatePercent = percent;
}


void
EvoOptions::setMutationOutput (int amount)
{
  this->mutationOptions->mutationOutput = amount;
}


void
EvoOptions::setSimulationEndDelay(int delay)
{
  this->selectionOptions->simulationOptions->endDelay = delay;
}

void
EvoOptions::setSelectionOutput (int amount)
{
  this->selectionOptions->selectionOutput = amount;
}

void
EvoOptions::setEpochsLimit(int epochsLimit)
{
  this->epochsLimit = epochsLimit;
}



void
EvoOptions::setEvolutionAccurency(double accurancy)
{
  this->selectionOptions->evolutionAccurancy = accurancy;
}
