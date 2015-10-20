// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Options.h"
#include "EvoAgent.h"
#include "EvaluatedAgent.h"
#include "Genom.h"


/**
 * 
 */
class  MutationController
{
public:
	MutationController();
	~MutationController();

  MutationController(MutationOptions*);

  EvoAgentsGroup* mutateAgents(EvoAgentsGroup*);
  EvoAgentsGroup* mutateAgents(EvaluatedAgentsGroup*);

private:
  MutationOptions* options;

  EvoAgent*       mutate(EvoAgent*);
  EvaluatedAgent* mutate(EvaluatedAgent*);

  void neuronsDeleteSection(Genom*);
  void neuronsCreateSection(Genom*);
  void synapsesDeleteSection(Genom*);
  void synapsesCreateSection(Genom*);


  int getNeuronsDeleteAmout(Genom*, double);
  int getNeuronsCreateAmout(Genom*, double);
  int getSynapsesDeleteAmout(Genom*, double);
  int getSynapsesCreateAmout(Genom*, double);

};
