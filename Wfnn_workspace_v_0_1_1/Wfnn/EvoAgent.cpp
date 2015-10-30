// Fill out your copyright notice in the Description page of Project Settings.


#include "EvoAgent.h"

EvoAgent::EvoAgent()
{
}

EvoAgent::~EvoAgent()
{
}


EvoAgent::EvoAgent(EvoAgent* source)
{
  this->genom = new Genom(source->genom);

  NetworkManager networkManager;

  this->network =  networkManager.createFromGenom(this->genom);
}



EvoAgentsGroup::EvoAgentsGroup()
{

}


EvoAgentsGroup::EvoAgentsGroup(EvoAgent* agent)
{
  agents.emplace_back(agent);
}

void
EvoAgentsGroup::add(EvoAgent* agent)
{
  agents.emplace_back(agent);
}

int
EvoAgentsGroup::size()
{
  return agents.size();
}

EvoAgent*
EvoAgentsGroup::operator[](int index)
{
  return agents[index];
}

