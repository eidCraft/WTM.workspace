// Fill out your copyright notice in the Description page of Project Settings.


#include "Genom.h"

Genom::Genom(){}


Genom::~Genom()
{
}


Genom::Genom(Genom* genom)
{
//  vector<int> neurons;
//  NetworkOptions* options;
//  int maxNeuronId;

 //  vector<StoredSynapse*> synapses;

  this->maxNeuronId = genom->maxNeuronId;
  this->options = genom->options;
  this->neurons = genom->neurons;

  this->synapses = vector<StoredSynapse*>();
  for (StoredSynapse* synapse : genom->synapses)
  {
    this->synapses.emplace_back(new StoredSynapse(synapse));
  }

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

StoredSynapse::StoredSynapse(){}

StoredSynapse::StoredSynapse(StoredSynapse* synapse)
{
  this->presynapticNeuron = synapse->presynapticNeuron;
  this->postsynapticNeuron = synapse->postsynapticNeuron;

  this->length = synapse->length;
  this->weigth = synapse->weigth;
}
