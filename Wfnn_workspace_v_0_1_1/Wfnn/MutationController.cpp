// Fill out your copyright notice in the Description page of Project Settings.


#include "MutationController.h"

MutationController::MutationController()
{
}

MutationController::~MutationController()
{
}


#include "EvaluatedAgent.h"


MutationController::MutationController(MutationOptions* options)
{
  this->options = options;
}


EvoAgentsGroup*
MutationController::mutateAgents(EvoAgentsGroup* agents)
{
  EvoAgentsGroup* destGroup = new EvoAgentsGroup();

  int agentsAmount = agents->size();
  for (int i = 0; i != agentsAmount; i++)
  {
    int mutantsFromEachAgent = options->mutationOutput;
    for (int j = 0; j < mutantsFromEachAgent; j++)
    {
      EvoAgent* newMutant = mutate((*agents)[i]);
      destGroup->add(newMutant);
    }
  }
  return destGroup;
}


EvoAgent*
MutationController::mutate(EvoAgent* sourceAgent)
{
  EvoAgent* destAgent = new EvoAgent(sourceAgent);

  neuronsDeleteSection(destAgent->genom);
  neuronsCreateSection(destAgent->genom);

  synapsesDeleteSection(destAgent->genom);
  synapsesCreateSection(destAgent->genom);

  return destAgent;
}

EvaluatedAgent*
MutationController::mutate(EvaluatedAgent* sourceAgent)
{
  EvaluatedAgent* destAgent = new EvaluatedAgent(sourceAgent);

  neuronsDeleteSection(destAgent->genom);
  neuronsCreateSection(destAgent->genom);

  synapsesDeleteSection(destAgent->genom);
  synapsesCreateSection(destAgent->genom);

  return destAgent;
}



void
MutationController::neuronsDeleteSection(Genom* genom)
{

  int maxIndex = genom->neurons.size();

  int deleteAmount = getNeuronsDeleteAmout(
    genom, options->neuronsDeletePercent);


  int deleteIndex;
  for (int i = 0; i < deleteAmount; i++)
  {
    deleteIndex = rand() % maxIndex;
    genom->removeNeuron(deleteIndex);
    maxIndex--;
  }
}

void
MutationController::neuronsCreateSection(Genom* genom)
{
  int createAmount = getNeuronsCreateAmout(
    genom, options->neuronsCreatePercent);

  for (int i = 0; i < createAmount; i++)
  {
    genom->addNeuron();
  }
}


void
MutationController::synapsesDeleteSection(Genom* genom)
{
  int maxIndex = genom->synapses.size();

  int deleteAmount = getSynapsesDeleteAmout(
    genom, options->synapsesDeletePercent);

  int deleteIndex;
  for (int i = 0; i < deleteAmount; i++)
  {
    deleteIndex = rand() % maxIndex;
    genom->removeSynapse(deleteIndex);
    maxIndex--;
  }
}


void
MutationController::synapsesCreateSection(Genom* genom)
{
  int createAmount = getSynapsesCreateAmout(
    genom, options->synapsesDeletePercent);

  StoredSynapse* newSynapse;
  int preNeuronIndex;
  int postNeuronIndex;

  for (int i = 0; i < createAmount; i++)
  {
    newSynapse = new StoredSynapse();

    preNeuronIndex = rand() % genom->neurons.size();
    postNeuronIndex = (preNeuronIndex +
      (rand() % (genom->neurons.size() - 1))) % genom->neurons.size();

    newSynapse->length = 1 + rand() % (genom->options->maximumLinkLength - 1);
    newSynapse->weigth = 5 + rand() % 15;

    newSynapse->presynapticNeuron = genom->neurons[preNeuronIndex];
    newSynapse->postsynapticNeuron = genom->neurons[postNeuronIndex];

    genom->addSynapse(newSynapse);
  }
}


int
MutationController::getNeuronsDeleteAmout(Genom* genom, double percent)
{
  double totalAmount = genom->neurons.size() * percent;
  return static_cast<int>(totalAmount);
}

int
MutationController::getNeuronsCreateAmout(Genom* genom, double percent)
{
  double totalAmount = genom->neurons.size() * percent;
  return static_cast<int>(totalAmount);
}

int
MutationController::getSynapsesDeleteAmout(Genom* genom, double percent)
{
  double totalAmount = genom->synapses.size() * percent;
  return static_cast<int>(totalAmount);
}

int
MutationController::getSynapsesCreateAmout(Genom* genom, double percent)
{
  double totalAmount = genom->synapses.size() * percent;
  return static_cast<int>(totalAmount);
}
