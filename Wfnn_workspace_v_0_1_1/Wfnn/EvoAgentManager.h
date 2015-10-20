// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetworkManager.h"
#include "GenomManager.h"

#include "EvoAgent.h"


/**
 * 
 */
class  EvoAgentManager
{
public:
	EvoAgentManager();
	~EvoAgentManager();

  EvoAgent* load(std::string);

private:
  NetworkManager* networkManager;
  GenomManager*   genomManager;

};
