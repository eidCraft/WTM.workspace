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

  EvaluatedAgentsGroup* select(EvaluatedAgentsGroup*);

private:
  void selectNarrowWay(EvaluatedAgentsGroup*, EvaluatedAgentsGroup*);
  void selectWideWay(EvaluatedAgentsGroup*, EvaluatedAgentsGroup*);

};
