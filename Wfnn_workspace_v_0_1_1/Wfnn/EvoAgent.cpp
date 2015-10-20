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
  this->genom = source->genom;
  this->network = source->network;
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

