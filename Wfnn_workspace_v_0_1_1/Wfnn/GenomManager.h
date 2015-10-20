// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "string"

#include "Genom.h"


/**
 * 
 */
class  GenomManager
{
public:
	GenomManager();
	~GenomManager();

  Genom* loadGenom(std::string);

private:
  void loadOptions(ifstream&, Genom*);
  void loadNeurons(ifstream&, Genom*);
  void loadSynapses(ifstream&, Genom*);

  void separateAndDissolveValues(
    ifstream&, Genom*,
    void (GenomManager::*f)(Genom*, string));

  void yieldOptionsFill(Genom*, string);
  void yieldNeuronsFill(Genom*, string);
  void yieldSynapsesFill(Genom*, string);


};
