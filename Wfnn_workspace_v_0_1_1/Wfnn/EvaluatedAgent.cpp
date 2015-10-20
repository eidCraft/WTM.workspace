// Fill out your copyright notice in the Description page of Project Settings.


#include "EvaluatedAgent.h"

EvaluatedAgent::EvaluatedAgent()
{
}

EvaluatedAgent::~EvaluatedAgent()
{
}


EvaluatedAgent::EvaluatedAgent(TestedAgent *agent)
{
  this->genom     = agent->genom;
  this->network   = agent->network;
  this->results   = agent->results;
  this->scenarios = agent->scenarios;
}


int
EvaluatedAgent::getMarksAmount()
{
  return marks.size();
}

void
EvaluatedAgent::addMark(double mark)
{
  marks.emplace_back(mark);
}


EvaluatedAgentsGroup::EvaluatedAgentsGroup()
{

}


EvaluatedAgentsGroup::EvaluatedAgentsGroup(EvaluatedAgent* agent)
{
  agents.at(0) = agent;
}


EvoAgentsGroup*
EvaluatedAgentsGroup::reduceToEvoAgents()
{
  EvoAgentsGroup* destGroup = new EvoAgentsGroup();

  for (auto agent : agents)
  {
    destGroup->add(static_cast<EvoAgent*>(agent));
  }
  return destGroup;
}


void
EvaluatedAgentsGroup::add(EvaluatedAgent* agent)
{
  agents.emplace_back(agent);
}


int
EvaluatedAgentsGroup::getAgentsAmount()
{
  return agents.size();
}


int
EvaluatedAgentsGroup::getMarksAmount()
{
  return agents.at(0) ? agents.at(0)->getMarksAmount() : -1;
}

EvaluatedAgent*
EvaluatedAgentsGroup::operator[](int index)
{
  return agents.at(index);
}
