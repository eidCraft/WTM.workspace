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
SelectionArbiter::select(EvaluatedAgentsGroup* initialGroup, size_t amount)
{
  EvaluatedAgentsGroup* finalGroup = new EvaluatedAgentsGroup();

  selectTopAgents(initialGroup, finalGroup, amount);

  //selectWideWay(initialGroup, finalGroup);

  return finalGroup;
}



void
SelectionArbiter::selectTopAgents(EvaluatedAgentsGroup* initialGroup,
  EvaluatedAgentsGroup* finalGroup, size_t amount)
{
  size_t nAgents = amount <= initialGroup->agents.size() ?
    amount : initialGroup->agents.size();

  for (size_t iAgent = 0; iAgent != nAgents; iAgent++)
  {
    finalGroup->add(initialGroup->agents[iAgent]);
  }

}


void
SelectionArbiter::selectWideWay(EvaluatedAgentsGroup* initialGroup,
  EvaluatedAgentsGroup* finalGroup)
{

}

//void
//SelectionArbiter::sortByMark(EvaluatedAgentsGroup* evaluatedAgentsGroup)
//{
//  vector<int> totalMark (evaluatedAgentsGroup-> )




//  for (int i = 0; i < A.Length; i++)
//  {
//    for (int j = i+1; j < A.Length; j++)
//    {
//      if (A[j] < A[i])
//      {
//        var temp = A[i];
//        A[i] = A[j];
//        A[j] = temp;
//      }
//    }
//  }
//}
