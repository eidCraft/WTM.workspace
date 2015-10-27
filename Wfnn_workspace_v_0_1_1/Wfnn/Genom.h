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

  vector<int> neurons;
  vector<StoredSynapse*> synapses;
  NetworkOptions* options;

  int maxNeuronId;

  void addNeuron();
  void addSynapse(StoredSynapse*);
  void removeNeuron(int);
  void removeSynapse(int);

private:

};


class  StoredSynapse
{
  StoredSynapse();
  StoredSynapse(StoredSynapse*);

  int presynapticNeuron;
  int postsynapticNeuron;

  double length;
  double weigth;
};
