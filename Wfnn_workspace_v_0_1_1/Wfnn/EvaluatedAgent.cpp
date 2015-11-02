// Fill out your copyright notice in the Description page of Project Settings.


#include "EvaluatedAgent.h"

EvaluatedAgent::EvaluatedAgent()
{
}

EvaluatedAgent::~EvaluatedAgent()
{
  this->totalMark = 0;
}


EvaluatedAgent::EvaluatedAgent(TestedAgent *agent)
{
  this->genom     = agent->genom;
  this->network   = agent->network;
  this->results   = agent->results;
  this->scenarios = agent->scenarios;

  this->totalMark = 0;
}

EvaluatedAgent::EvaluatedAgent(EvoAgent *agent)
{
  this->genom     = agent->genom;
  this->network   = agent->network;

  this->totalMark = 0;
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

EvaluatedAgentsGroup::EvaluatedAgentsGroup(EvoAgent* agent)
{
  agents = vector<EvaluatedAgent*>();
  agents.emplace_back(new EvaluatedAgent(agent));
}

//EvaluatedAgentsGroup::EvaluatedAgentsGroup(EvaluatedAgent* agent)
//{
//  agents.at(0) = agent;
//}


EvoAgentsGroup*
EvaluatedAgentsGroup::reduceToEvoAgents()
{
  EvoAgentsGroup* destGroup = new EvoAgentsGroup();

  for (auto agent : agents)
  {
    destGroup->add(static_cast<EvoAgent*>(agent));
    //destGroup->add(agent);
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


void
EvaluatedAgentsGroup::swapAgents(int x, int y)
{
  EvaluatedAgent* tmp;

  tmp = agents.at(x);
  agents.at(x) = agents.at(y);
  agents.at(y) = tmp;
}


void
EvaluatedAgentsGroup::sortByMark()
{
  size_t nAgents = agents.size();
  size_t nMarks  = agents.at(0)->marks.size();

  for (size_t i = 0; i != nAgents; i ++)
  {
    for (size_t j = 0; j != nMarks; j ++)
    {
      agents.at(i)->totalMark += agents.at(i)->marks.at(j);
    }
  }

  int i, j;
  for (i = nAgents - 1; i >= 0; i--)
  {
    for (j = 0; j < i; j++)
    {
      if (agents.at(j)->totalMark > agents.at(j+1)->totalMark)
        swapAgents(j, j + 1);
    }
  }
}

size_t
EvaluatedAgentsGroup::size()
{
  return agents.size();
}

