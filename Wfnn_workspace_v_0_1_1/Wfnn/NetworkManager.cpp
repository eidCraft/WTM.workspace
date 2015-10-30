// Fill out your copyright notice in the Description page of Project


#include "NetworkManager.h"

#include <stdio.h>
#include <fstream>
#include <string>


#include "EvoAgent.h"
#include "Network.h"
#include "Genom.h"

class Network;

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}






Network*
NetworkManager::loadNetwork(string filename)
{
  Network* network = new Network();

  ifstream source(filename);

  bool isFileValid = isIdentificatorValid(source);
  if (!isFileValid)
  {
    //GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString("File doesn't contain Network"));
  }

  loadNetworkName(source, network);
  loadNetworkOptions(source, network);
  loadNetworkNeurons(source, network);
  loadNetworkSynapses(source, network);
  loadNetworkInputs(source, network);
  loadNetworkOutputs(source, network);

  source.close();
  return network;
}


void
NetworkManager::saveNetwork(string filename, Network* source)
{
  std::ofstream dest(filename);

  // ----------------------------------------------------------//
  dest << "Network" << " ";

  // ----------------------------------------------------------//
  dest << source->name << ";" << " ";

  // ----------------------------------------------------------//
  dest << source->options->activationThreshold << ";";
  dest << source->options->activityDuration << ";";
  dest << source->options->relaxationDuration << ";";
  dest << source->options->addlChargeLeak << ";";
  dest << source->options->addlChargeIncriment << ";" << " ";

  // ----------------------------------------------------------//
  for (auto &neuron : source->neurons)
  {
    dest << neuron->getId() << ";";
  }
  dest << " ";

  // ----------------------------------------------------------//
  for (auto &neuron : source->neurons)
  {
    for (auto &synapse : neuron->synapses)
    {
      dest << neuron->id << ";";
      dest << synapse->postNeuron->id << ";";
      dest << synapse->linkLenght << ";";
      dest << synapse->linkWeight << ";";
    }
  }
  dest << " ";

  // ----------------------------------------------------------//
  for (auto &id : source->inputNeurons)
  {
    dest << id << ";";
  }
  dest << " ";

  // ----------------------------------------------------------//
  for (auto &id : source->outputNeurons)
  {
    dest << id << ";";
  }
  dest << " ";
}




bool
NetworkManager::isIdentificatorValid(ifstream& source)
{
  string    identificator;
  source >> identificator;

  bool   isValid = (identificator == "WfnnNetwork");
  return isValid;
}



void
NetworkManager::loadNetworkName(
ifstream& fin, Network* network)
{
  string   name;
  fin >> name;
  network->name = name;
}

void
NetworkManager::loadNetworkOptions(
ifstream& source, Network* network)
{
  separateAndDissolveValues(
    source, network,
    &NetworkManager::yieldNetworkParametersFill
    );
}

void
NetworkManager::loadNetworkNeurons(
ifstream& source, Network* network)
{
  separateAndDissolveValues(
    source, network,
    &NetworkManager::yieldNetworkNeuronsFill
    );
}

void
NetworkManager::loadNetworkSynapses(
ifstream& source, Network* network)
{
  separateAndDissolveValues(
    source, network,
    &NetworkManager::yieldNetworkSynapsesFill
    );
}

void
NetworkManager::loadNetworkInputs(
ifstream& source, Network* network)
{
  separateAndDissolveValues(
    source, network,
    &NetworkManager::yieldNetworkInputsFill
    );
}

void
NetworkManager::loadNetworkOutputs(
ifstream& source, Network* network)
{
  separateAndDissolveValues(
    source, network,
    &NetworkManager::yieldNetworkOutputsFill
    );

  network->outputNeuronsAmount = network->outputNeurons.size();
}



void
NetworkManager::separateAndDissolveValues(
ifstream& fin, Network* network,
void (NetworkManager::*f)(Network*, double))
{
  string entireString;
  string part;

  fin >> entireString;

  std::size_t found = entireString.find(";");

  bool isFound = (found != std::string::npos);
  if (isFound)
  {

    part = entireString.substr(0, found);

    entireString = entireString.substr(found + 1,
      entireString.size() - found);

    while (!part.empty())
    {
      (this->*f)(network, std::stod(part));

      found = entireString.find(";");
      part = entireString.substr(0, found);

      entireString = entireString.substr(found + 1,
        entireString.size() - found);
    }
  }
  else
  {
    //// cout << "Can't find separator. Incorrect data." << endl;
    //GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString("Can't find separator. Incorrect data."));
  }
}



void
NetworkManager::yieldNetworkParametersFill(
Network* network, double value)
{
  static int progressIndex;

  switch (progressIndex)
  {
  case 8:
    // сброс индекса (т.к. он сохраняется между созданием разных сетей)
    progressIndex = 0;
  case 0:
    network->options->activationThreshold = value;
    break;
  case 1:
    network->options->activityDuration = static_cast<int>(value);
    break;
  case 2:
    network->options->relaxationDuration = static_cast<int>(value);
    break;
  case 3:
    network->options->addlChargeLeak = value;
    break;
  case 4:
    network->options->addlChargeIncriment = value;
    break;
  case 5:
    network->options->linkPowerIncrement = value;
    break;
  case 6:
    network->options->maximumLinkLength = static_cast<int>(value);
    break;
  case 7:
    network->options->maximumSynapicWeigth = static_cast<int>(value);
    break;
  default:
    // cout << "Index is out of NetworkParameters" << endl;
    break;
  }
  progressIndex++;
}



void
NetworkManager::yieldNetworkNeuronsFill(
Network* network, double id)
{
  Neuron* newNeuron = new Neuron(network->options, static_cast<int>(id));
  network->neurons.emplace_back(newNeuron);
}



void
NetworkManager::yieldNetworkSynapsesFill(
Network* network, double value)
{
  static int yieldProgressIndex;
  static Synapse* lastSynapse;

  switch (yieldProgressIndex)
  {
    case 4:
    {
      yieldProgressIndex = 0;
    }

    case 0:
    {
      int id = static_cast<int>(value);

      Neuron* lastNeuron = network->findNeuronById(id);

      lastNeuron->synapses.emplace_back(new Synapse);

      lastSynapse = lastNeuron->synapses.back();
    }
    break;

    case 1:
    {
      int id = static_cast<int>(value);

      Neuron* neuron = network->findNeuronById(id);

      lastSynapse->postNeuron = neuron;
    }
    break;

    case 2:
    {
      int length = static_cast<int>(value);
      lastSynapse->linkLenght = length;
    }
    break;

    case 3:
    {
      lastSynapse->linkWeight = value;
    }
    break;

    default:
    {
      // cout << "Out of yieldProgessIndex. Do something." << endl;
    }
    break;
  }

  bool isEndOfSynapsDescription = (yieldProgressIndex == 3);
  if (isEndOfSynapsDescription)
  {
    yieldProgressIndex = 0;
  }
  else
  {
    yieldProgressIndex++;
  }
}




void
NetworkManager::yieldNetworkInputsFill(
Network* network, double value)
{
  int id = static_cast<int>(value);
  Neuron* neuron = network->findNeuronById(id);
  network->inputNeurons.emplace_back(neuron);
}



void
NetworkManager::yieldNetworkOutputsFill(
Network* network, double value)
{
  int id = static_cast<int>(value);
  Neuron* neuron = network->findNeuronById(id);
  network->outputNeurons.emplace_back(neuron);
}







Network*
NetworkManager::createFromGenom(Genom* genom)
{
  Network* network = new Network();

  loadNetworkName(genom, network);
  loadNetworkOptions(genom, network);
  loadNetworkNeurons(genom, network);
  loadNetworkSynapses(genom, network);
  loadNetworkInputs(genom, network);
  loadNetworkOutputs(genom, network);

  return network;
}


void
NetworkManager::loadNetworkName(
Genom* genom, Network* network)
{
  network->name = genom->name;
}


void
NetworkManager::loadNetworkOptions(
Genom* genom, Network* network)
{
  network->options = genom->options;
}


void
NetworkManager::loadNetworkNeurons(
Genom* genom, Network* network)
{
  Neuron* newNeuron;

  for (int neuronId : genom->neurons)
  {
    newNeuron= new Neuron(network->options, neuronId);
    network->neurons.emplace_back(newNeuron);
  }
}



//vector<int> neurons;
//vector<StoredSynapse*> synapses;
//NetworkOptions* options;

//int maxNeuronId;


//int presynapticNeuron;
//int postsynapticNeuron;

//double length;
//double weigth;


void
NetworkManager::loadNetworkSynapses(
Genom* genom, Network* network)
{
  Synapse* newSynapse;
  for (StoredSynapse* storedSynapse : genom->synapses)
  {
    newSynapse = new Synapse();

    newSynapse->linkLenght = storedSynapse->length;
    newSynapse->linkWeight = storedSynapse->weigth;
    newSynapse->postNeuron = network->findNeuronById(storedSynapse->postsynapticNeuron);

    network->findNeuronById(storedSynapse->presynapticNeuron)->synapses.emplace_back(newSynapse);
     }
}

void
NetworkManager::loadNetworkInputs(Genom* genom, Network* network)
{
  for (int inputNeuronId : genom->inputNeurons)
  {
    network->inputNeurons.emplace_back(network->findNeuronById(inputNeuronId));
  }
}


void
NetworkManager::loadNetworkOutputs(Genom* genom, Network* network)
{
  for (int outputNeuronId : genom->outputNeurons)
  {
    network->outputNeurons.emplace_back(network->findNeuronById(outputNeuronId));
  }
}






