// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EvaluatedAgent.h"

class EvaluatedAgentsGroup;


/**
 * 
 */
class  SelectionArbiter
{
public:
	SelectionArbiter();
	~SelectionArbiter();

  EvaluatedAgentsGroup* select(EvaluatedAgentsGroup*, size_t);

private:
  void selectTopAgents(EvaluatedAgentsGroup*, EvaluatedAgentsGroup*, size_t);
  void selectWideWay(EvaluatedAgentsGroup*, EvaluatedAgentsGroup*);

};
