// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "Options.h"
#include "NetworkManager.h"


class Synapse;
class NetworkManager;

/**
*
*/
class Neuron
{
public:
  Neuron();
  Neuron(Neuron*);
  ~Neuron();

  friend NetworkManager;

  bool isNeuronActiv;
  bool isNeuronRelax;
  bool isNeuronInactiv;

  Neuron(NetworkOptions*, int);

  void   goToActiveState();
  void   goToRelaxState();
  void   goToInactiveState();

  void   goToActivationPoint();

  bool   isActiv();
  bool   isRelax();
  bool   isInactiv();

  void incrementCounters();
  void removeNextCharge();
  void addLeak();
  void makeChargeStep();
  void addBaseChargeLikeNetworkInput(double);

  bool isOnNextMomentNeuronCanTakeCharge();

  bool   isActivityTimeExceeded();
  bool   isRelaxationTimeExceeded();
  bool   isActivationThresholdExceeded();

  double getCurrentFullCharge();
  double getCurrentBaseCharge();
  double getCurrentAddlCharge();

  double getThreshold();

  int    getShiftedBaseChargeIndex(int);

  void   addBaseChargeBeforehand(int, double);
  void   removeCurrentBaseCharge();

  void   correctLinks();
  void   spreadNeuronActivity();
  void   moveToNextTact();

  int    getId();

  std::string toString();


  int id;
  NetworkOptions* options;
  std::vector<Synapse*> synapses;

  int relaxationTime;
  int activityTime;

  std::vector<double> baseCharges;
  int baseChargeIndex;

  double addlCharge;
  double fullCharge;


  bool relaxWillEnd();

  std::vector< std::vector<Synapse*> >* signalsSources;

  void initializeBaseCharges();
  void sendSynapticSignal(int, double, Synapse*);
  void saveSignalSource(int, Synapse*);
  void linksCorrectFunction(double*);

};

class  Synapse
{
public:
  Synapse();
  Synapse(Synapse*, Neuron *postNeuron);

  int     linkLenght;
  double  linkWeight;
  Neuron* postNeuron;
};
