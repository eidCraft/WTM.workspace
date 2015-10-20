// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionArbiter.h"

SelectionArbiter::SelectionArbiter()
{
}

SelectionArbiter::~SelectionArbiter()
{
}




#include "SelectionArbiter.h"



EvaluatedAgentsGroup*
SelectionArbiter::select(EvaluatedAgentsGroup* initialGroup)
{
  EvaluatedAgentsGroup* finalGroup = new EvaluatedAgentsGroup();

  selectNarrowWay(initialGroup, finalGroup);

  selectWideWay(initialGroup, finalGroup);

  return finalGroup;
}



void
SelectionArbiter::selectNarrowWay(EvaluatedAgentsGroup* initialGroup,
  EvaluatedAgentsGroup* finalGroup)
{
  vector<int> bestAgentsIndexes;

  double bestMark = 0;
  int    bestMarkOwner;
  bool   isNewMax;

  int agensAmount = initialGroup->getAgentsAmount();
  int marksAmount = initialGroup->getMarksAmount();

  bool isAlreadyInBestAgents;
  for (int i = 0; i < marksAmount; i++)
  {
    for (int j = 0; j < agensAmount; j++)
    {
      isNewMax = ( (*initialGroup)[j]->marks[i] > bestMark);
      if (isNewMax)
      {
        bestMark = (*initialGroup)[j]->marks[i];
        bestMarkOwner = j;
      }
    }
    isAlreadyInBestAgents = std::find(
      bestAgentsIndexes.begin(), bestAgentsIndexes.end(), bestMarkOwner) ==
      bestAgentsIndexes.end();

    if (! isAlreadyInBestAgents)
    {
      bestAgentsIndexes.emplace_back(bestMarkOwner);
    }
  }

  int totalAgentsAmount = bestAgentsIndexes.size();
  for (int i = 0; i < totalAgentsAmount; i++)
  {
    finalGroup->add((*initialGroup)[bestAgentsIndexes[i]]);
  }
}


void
SelectionArbiter::selectWideWay(EvaluatedAgentsGroup* initialGroup,
  EvaluatedAgentsGroup* finalGroup)
{

}
