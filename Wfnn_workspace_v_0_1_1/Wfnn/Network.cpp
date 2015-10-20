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


  int neuronsAmount = neurons.size();
  for (int i = 0; i != neuronsAmount; i++)
  {

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
        //char buff[20];
        //itoa(i, buff, 10);
        //GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString(buff));

        neurons[i]->spreadNeuronActivity();
      }
    }
    else
    {
      neurons[i]->addLeak();

      bool isNeuronRelax = neurons[i]->isRelax();
      if (isNeuronRelax)
      {
        bool isTimeToStopRelax = neurons[i]->isRelaxationTimeExceeded();
        if (isTimeToStopRelax)
        {
          neurons[i]->goToInactiveState();
        }
      }
      else
      {
        bool isTimeToActivate = neurons[i]->isActivationThresholdExceeded();
        if (isTimeToActivate)
        {
          neurons[i]->goToActiveState();
        }
      }
    }
    neurons[i]->makeChargeStep();
    neurons[i]->incrementCounters();

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
