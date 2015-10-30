// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <vector>

using std::vector;
using std::string;

#include "Neuron.h"

class StoredSynapse;



/**
 * 
 */
class  Genom
{
public:
	Genom();
  Genom(Genom*);
	~Genom();

  string name;

  vector<int> neurons;
  vector<StoredSynapse*> synapses;
  NetworkOptions* options;

  vector<int> inputNeurons;
  vector<int> outputNeurons;

  int maxNeuronId;

  void addNeuron();
  void addSynapse(StoredSynapse*);
  void removeNeuron(int);
  void removeSynapse(int);


};


class  StoredSynapse
{
public:
  StoredSynapse();
  StoredSynapse(StoredSynapse*);

  int presynapticNeuron;
  int postsynapticNeuron;

  double length;
  double weigth;
};
