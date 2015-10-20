// Fill out your copyright notice in the Description page of Project Settings.


#include "Genom.h"


Genom::~Genom()
{
}


Genom::Genom()
{
  this->options = new NetworkOptions();
}


void
Genom::addNeuron()
{
  int newNeuoronId = maxNeuronId + 1;
  neurons.emplace_back(newNeuoronId);

  maxNeuronId++;
}

void
Genom::addSynapse(StoredSynapse* addlSynapse)
{
  synapses.emplace_back(addlSynapse);
}

void
Genom::removeNeuron(int removeIndex)
{
  neurons.erase(neurons.begin() + removeIndex);
}

void
Genom::removeSynapse(int removeIndex)
{
  synapses.erase(synapses.begin() + removeIndex);
}