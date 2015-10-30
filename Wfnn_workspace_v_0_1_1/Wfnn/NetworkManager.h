// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <fstream>
#include <string>

using std::ifstream;
using std::string;

#include "Network.h"
#include "Genom.h"

class Genom;
class Network;

/**
 * 
 */
class  NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

  Network* loadNetwork(string);
  void     saveNetwork(string, Network*);

  Network* createFromGenom(Genom*);

private:
  bool isIdentificatorValid(ifstream&);

  void loadNetworkName(ifstream&, Network*);
  void loadNetworkOptions(ifstream&, Network*);
  void loadNetworkNeurons(ifstream&, Network*);
  void loadNetworkSynapses(ifstream&, Network*);
  void loadNetworkInputs(ifstream&, Network*);
  void loadNetworkOutputs(ifstream&, Network*);

  void separateAndDissolveValues(
    ifstream&, Network*,
    void (NetworkManager::*f)(Network*, double)
    );

  void yieldNetworkParametersFill(Network*, double);
  void yieldNetworkNeuronsFill(Network*, double);
  void yieldNetworkSynapsesFill(Network*, double);
  void yieldNetworkInputsFill(Network*, double);
  void yieldNetworkOutputsFill(Network*, double);




  void loadNetworkName(Genom*, Network*);
  void loadNetworkOptions(Genom*, Network*);
  void loadNetworkNeurons(Genom*, Network*);
  void loadNetworkSynapses(Genom*, Network*);
  void loadNetworkInputs(Genom*, Network*);
  void loadNetworkOutputs(Genom*, Network*);



};
