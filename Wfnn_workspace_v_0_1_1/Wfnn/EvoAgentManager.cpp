// Fill out your copyright notice in the Description page of Project Settings.


#include "EvoAgentManager.h"
#include "NetworkManager.h"
#include "GenomManager.h"


EvoAgentManager::~EvoAgentManager()
{
}



EvoAgentManager::EvoAgentManager()
{
  networkManager = new NetworkManager();
  genomManager = new GenomManager();
}


EvoAgent*
EvoAgentManager::load(std::string filename)
{
  EvoAgent* destAgent = new EvoAgent();

  destAgent->network = networkManager->loadNetwork(filename);
  destAgent->genom = genomManager->loadGenom(filename);

  return destAgent;
}
