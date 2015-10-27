// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

using std::vector;

#include "Network.h"
#include "Genom.h"

class EvoAgent;
class EvoAgentsGroup;


/**
 * 
 */
class  EvoAgent
{
public:
	EvoAgent();
	~EvoAgent();

  Network* network;
  Genom*   genom;

  EvoAgent(EvoAgent *);

private:

};


class  EvoAgentsGroup
{
public:
  EvoAgentsGroup();
  EvoAgentsGroup(EvoAgent*);

  void add(EvoAgent*);
  int  size();

  EvoAgent* operator[](int);

private:
  vector<EvoAgent*> agents;

};
