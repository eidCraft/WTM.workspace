// Fill out your copyright notice in the Description page of Project

#include "Neuron.h"

#include <sstream>

#include "Options.h"


Neuron::Neuron()
{
}

Neuron::~Neuron()
{
}




Neuron::Neuron(NetworkOptions* options, int id)
{
  this->options = options;
  this->id = id;
  this->relaxationTime = 0;
  this->activityTime = 0;
  this->baseChargeIndex = 0;
  this->addlCharge = 0;
  this->fullCharge = 0;

  this->initializeBaseCharges();

  isNeuronActiv = false;
  isNeuronRelax = false;
  isNeuronInactiv = true;
}



void
Neuron::initializeBaseCharges()
{
  int capacity = this->options->maximumLinkLength;
  baseCharges = vector<double>(capacity, 0.0);
}



bool
Neuron::isActiv()
{
  return isNeuronActiv;
}

bool
Neuron::isRelax()
{
  return isNeuronRelax;
}

bool
Neuron::isInactiv()
{
  return  isNeuronInactiv;
}

bool
Neuron::isActivityTimeExceeded()
{
  bool   isExceeded = (activityTime > options->activityDuration);
  return isExceeded;
}

bool
Neuron::isRelaxationTimeExceeded()
{
  bool   isExceeded = (relaxationTime > options->relaxationDuration);
  return isExceeded;
}

bool
Neuron::isActivationThresholdExceeded()
{
  bool   isExceeded = (getCurrentFullCharge() >= options->activationThreshold);
  return isExceeded;
}



void
Neuron::goToActiveState()
{

  addlCharge += options->addlChargeIncriment;
  fullCharge = addlCharge;

  isNeuronInactiv = false;
  isNeuronActiv = true;
  isNeuronRelax = false;

}

void
Neuron::goToRelaxState()
{
  activityTime = 0;

  isNeuronInactiv = false;
  isNeuronActiv = false;
  isNeuronRelax = true;

  //correctLinks();
}

void
Neuron::goToInactiveState()
{
  relaxationTime = 0;

  isNeuronInactiv = true;
  isNeuronActiv = false;
  isNeuronRelax = false;

  removeCurrentBaseCharge();
}


void
Neuron::correctLinks()
{
  int synapsesAmount = synapses.size();
  for (int i = 0; i < synapsesAmount; i++)
  {
    bool isThisNeuronCauseActivity = synapses[i]->postNeuron->isActiv();
    if (isThisNeuronCauseActivity)
    {
      synapses[i]->linkWeight += options->linkPowerIncrement;
    }
  }
}


void
Neuron::spreadNeuronActivity()
{
  int synapsesAmount = synapses.size();
  for (int i = 0; i < synapsesAmount; i++)
  {
    synapses[i]->postNeuron->addBaseChargeBeforehand(
      synapses[i]->linkLenght,
      synapses[i]->linkWeight
      );
  }
}


void
Neuron::addBaseChargeBeforehand(int timeShift, double value)
{
  baseCharges[getShiftedBaseChargeIndex(timeShift)] += value;
}


void
Neuron::addBaseChargeLikeNetworkInput(double value)
{
  if (isNeuronInactiv)
  {
    baseCharges[baseChargeIndex] += value;
  }
}



void
Neuron::goToActivationPoint()
{
  double criticalCharge = this->options->activationThreshold + 1.0;

  addBaseChargeLikeNetworkInput(criticalCharge);

  //this->addBaseChargeBeforehand(0, criticalCharge);
}




void
Neuron::removeCurrentBaseCharge()
{
  baseCharges[baseChargeIndex] = 0;
}


void
Neuron::incrementCounters()
{
  if (isNeuronActiv)
  {
    activityTime++;
  }
  if (isNeuronRelax)
  {
    relaxationTime++;
  }
}

void
Neuron::addLeak()
{
  if (addlCharge >= options->addlChargeLeak)
  {
    addlCharge -= options->addlChargeLeak;
  }
  else
  {
    addlCharge = 0;
  }
}

void
Neuron::removeNextCharge()
{
  baseCharges[getShiftedBaseChargeIndex(1)] = 0;
}

bool
Neuron::isOnNextMomentNeuronCanTakeCharge()
{

  if (isActiv())
  {
    bool isEndOfActivity = activityTime + 1 >= options->activityDuration;
    if (! isEndOfActivity)
    {
      return false;
    }
  }
  if (isRelax())
  {
    bool isEndOfRelax = relaxationTime + 1 >= options->relaxationDuration;
    if (! isEndOfRelax)
    {
      return false;
    }
  }

  return true;
}
void
Neuron::makeChargeStep()
{
  bool isNeuronCanTakeCharge = isInactiv();


  if (!isNeuronCanTakeCharge)
  {
    removeNextCharge();
  }


  addBaseChargeBeforehand(1, baseCharges[baseChargeIndex]);


  baseCharges[baseChargeIndex] = 0;



  baseChargeIndex = getShiftedBaseChargeIndex(1);

}




int
Neuron::getShiftedBaseChargeIndex(int timeShift)
{
  int newIndex = (baseChargeIndex + timeShift);
  return newIndex  % baseCharges.size();
}



double
Neuron::getCurrentFullCharge()
{
  return baseCharges[baseChargeIndex] + addlCharge;
}

double
Neuron::getCurrentBaseCharge()
{
  return baseCharges[baseChargeIndex];
}

double
Neuron::getCurrentAddlCharge()
{
  return addlCharge;
}

int
Neuron::getId()
{
  return id;
}


string
Neuron::toString()
{
  std::ostringstream resultStream;

  resultStream << "Neuron id: " << id << std::endl;
  resultStream << "Charge:    " << getCurrentFullCharge() << std::endl;

  int synapsesAmount = synapses.size();
  for (int i = 0; i < synapsesAmount; i++)
  {
    resultStream << "  synaps:  " << i << std::endl;

    resultStream << "    postSynapsId: " <<
      synapses[i]->postNeuron->getId() << std::endl;

    resultStream << "    linkLenght:   " <<
      synapses[i]->linkLenght << std::endl;

    resultStream << "    linkWeight:   " <<
      synapses[i]->linkWeight << std::endl;
  }
  resultStream << std::endl;

  string result = resultStream.str();
  return result;
}
