// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include <vector>

using std::vector;
using std::string;

#include "Neuron.h"
#include "Options.h"
#include "NetworkManager.h"


class Neuron;
class NetworkManager;


/**
 * 
 */
class   Network
{
public:
	Network();
  Network(Network*);
	~Network();

  friend NetworkManager;

  string name;
  NetworkOptions* options;

  int  getInputsAmount();
  void makeSimulationTact();
  void setInputValues(vector<bool>);

  vector<bool> getOutputs();

  string toString();


  vector<Neuron*> neurons;

  vector<Neuron*> inputNeurons;
  vector<Neuron*> outputNeurons;

  //int inputNeuronsAmount;
  int outputNeuronsAmount;

  Neuron* findNeuronById(int);

};
