// Fill out your copyright notice in the Description page of Project Settings.

#include "Network.h"



Network::~Network()
{
}

Network::Network()
{
  this->options = new NetworkOptions;
}


vector<bool>
Network::getOutputs()
{
  vector<bool> values(outputNeuronsAmount);

  for (auto neuron : outputNeurons)
  {
    values.back() = neuron->isActiv();
  }

  return values;
}


Neuron*
Network::findNeuronById(int id)
{
  // neurons не установлен
  int neuronsAmount = neurons.size();
  for (int i = 0; i <= neuronsAmount; i++)
  {
    if (id == neurons[i]->getId())
    {
      return neurons[i];
    }
  }
  return nullptr;
}


// !!! Позже изменить формат данных на ассоциативный массив
void
Network::setInputValues(vector<bool> inputValues)
{
  int inputNeuronsAmount = inputNeurons.size();
  for (int i = 0; i < inputNeuronsAmount; i++)
  {
    bool isInputActiv = inputValues[i];
    if (isInputActiv)
    {
      inputNeurons[i]->goToActivationPoint();
    }
  }
}


void
Network::makeSimulationTact()
{
    //char str[20];
    //itoa(neurons[0]->getCurrentBaseCharge(), str, 10);

    //GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString("{"));
    //if (neurons[0]->isNeuronActiv)
    //{
    //  GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString("0 - activ"));
    //}
    //if (neurons[0]->isNeuronInactiv)
    //{
    //  GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString("0 - inactiv"));
    //}
    //if (neurons[0]->isNeuronRelax)
    //{
    //  GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString("0 - relax"));
    //}
    //GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString("}"));

    static int counter;
    counter ++;
  int neuronsAmount = neurons.size();
  for (int i = 0; i != neuronsAmount; i++)
  {

    bool isTimeToStopRelax = neurons[i]->isRelax() && neurons[i]->isRelaxationTimeExceeded();
    if (isTimeToStopRelax)
    {
      neurons[i]->goToInactiveState();
    }

    bool isTimeToActivate = neurons[i]->isInactiv() && neurons[i]->isActivationThresholdExceeded();
    if (isTimeToActivate)
    {
      neurons[i]->goToActiveState();
    }

    bool isNeuronActiv = neurons[i]->isActiv();
    if (isNeuronActiv)
    {
      bool isTimeToRelax = neurons[i]->isActivityTimeExceeded();
      if (isTimeToRelax)
      {
        neurons[i]->goToRelaxState();
      }
      else
      {
        neurons[i]->spreadNeuronActivity();
      }
    }
    else
    {
      neurons[i]->addLeak();
    }
    neurons[i]->incrementCounters();
    neurons[i]->makeChargeStep();
  }
}


string
Network::toString()
{
  string result;
  for (auto &neuron : neurons)
  {
    result += neuron->toString();
  }
  return result;
}


int
Network::getInputsAmount()
{
  return inputNeurons.size();
}


Network::Network(Network* network)
{
  this->name = network->name;
  this->options = network->options;
  this->outputNeuronsAmount = network->outputNeuronsAmount;

  this->neurons = new vector<Neuron*>(network->neurons.size());
  for (Neuron* neuron : network->neurons)
  {
    this->neurons.emplace_back(new Neuron(neuron));
  }

  this->inputNeurons = new vector<Neuron*>(network->inputNeurons.size());
  for (Neuron* neuron : network->inputNeurons)
  {
    this->inputNeurons.emplace_back(this->findNeuronById(neuron->id));
  }

  this->outputNeurons = new vector<Neuron*>(network->outputNeurons.size());
  for (Neuron* neuron : network->outputNeurons)
  {
    this->outputNeurons.emplace_back(this->findNeuronById(neuron->id));
  }
}
