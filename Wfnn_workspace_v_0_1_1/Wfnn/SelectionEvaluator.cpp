
#include "SelectionEvaluator.h"
#include "EvoAgent.h"

EvaluatedAgentsGroup*
SelectionEvaluator::evaluate(TestedAgentsGroup* testedAgents)
{
  EvaluatedAgentsGroup* evaluatedAgents = new EvaluatedAgentsGroup();

  int agentsAmount = testedAgents->agentsAmount();
  for (int i = 0; i < agentsAmount; i++)
  {
    evaluatedAgents->add(evaluateAgent((*testedAgents)[i]));
  }
  return evaluatedAgents;
}

EvaluatedAgent*
SelectionEvaluator::evaluateAgent(TestedAgent* testedAgent)
{
  EvaluatedAgent* evaluatedAgent = new EvaluatedAgent(testedAgent);

  int resultsAmount = testedAgent->resultsAmount();
  for (int i = 0; i < resultsAmount; i++)
  {
    evaluatedAgent->addMark( evaluateResult(
      (testedAgent->results)->at(i), (*testedAgent->scenarios)[i] ));
  }

  1;

  return evaluatedAgent;
}


double
SelectionEvaluator::evaluateResult(
  SimulationResult* result, Scenario* scenario)
{
  int resultsLength = result->length();
  int patternLength = scenario->outputData.size();

  vector< vector<double> > intermediateMarks(
    resultsLength, vector<double>(patternLength, 0.0f));

  for (int i = 0; i < resultsLength; i++)
  {
    for (int j = 0; j < patternLength; j++)
    {
      intermediateMarks[i][j] = getMatchingMark(
        result->data[i], scenario->outputData[j]);
    }
  }

  return finalEvaluation(intermediateMarks);
}



double
SelectionEvaluator::finalEvaluation(
  vector< vector<double> > intermediateResult)
{
  MatchingPrecedentsSet* precedents = new MatchingPrecedentsSet();

  for (size_t i = 0, iSize = intermediateResult.size(); i < iSize; i++)
  {
    for (size_t j = 0, jSize = intermediateResult.at(i).size(); j < jSize; j++)
    {
      precedents->addMember(intermediateResult[i][j], i, j);
    }
  }

  return precedents->getBestMark();
}




void
MatchingPrecedentsSet::addMember(double value, int outputNumber, int position)
{
  for (size_t i = 0, iLimit = precedents.size(); i < iLimit; i++)
  {
    if (i == outputNumber)
    {
      addNewMember(value, outputNumber, position);
      continue;
    }
    for (auto& precedent : precedents.at(i))
    {
      precedent->attemptToAddPart(value, outputNumber, position);
    }
  }
  precedents.emplace_back(vector<MatchingPrecedent*>());
}


void
MatchingPrecedent::attemptToAddPart(double value, int outputNumber, int position)
{
  int offset = position - lastMemberOutput;

  bool isMemeberSuitable = (offset > 0
    && position < lastMemberOutput +  5
    && outputNumber != lastMemberOutput);


  if (isMemeberSuitable)
  {
    addPart(value, outputNumber, position, offset);
  }

}


void
MatchingPrecedentsSet::addNewMember(double value, int outputNumber, int position)
{
  MatchingPrecedent* precedent = new MatchingPrecedent();

  precedent->totalMark        = value;
  precedent->lastMemberOutput = outputNumber;
  precedent->waitingPosition  = position;

  precedents.back().emplace_back(precedent);
}


void
MatchingPrecedent::addPart(
  double value, int outputNumber, int position, int offset)
{
  totalMark += value;
  totalMark += getDistanceMark(offset);
  lastMemberOutput = outputNumber;
  waitingPosition = position + 1;
}


double
MatchingPrecedent::getDistanceMark(int distance)
{
  return static_cast<double>(distance);
}


double
MatchingPrecedentsSet::getBestMark()
{
  double bestMark = 0.f;

  for (auto precedentsSet : precedents)
  {
    for (auto precedent : precedentsSet)
    {
      if (precedent->totalMark > bestMark)
      {
        bestMark = precedent->totalMark;
      }
    }
  }

  return bestMark;
}


vector<bool>
negation(vector<bool> initial)
{
  vector<bool> negative = initial;

  for(auto& value : negative)
  {
    value = (!value);
  }

  return negative;
}

int
multiplication(vector<bool> first, vector<bool> second)
{
  int result = 0;

  int size = first.size();
  for (int i = 0; i < size; i++)
  {
    result += (first[i] * second[i]);
  }

  return result;
}


double
SelectionEvaluator::getMatchingMark
  (vector<bool> row, vector<bool> pattern)
{
  double mark = 0.f;

  mark += multiplication(row, pattern);
  mark += multiplication(negation(row),negation(pattern));

  return mark;
}



SelectionEvaluator::SelectionEvaluator(EvaluationOptions* evaluationOptions)
{
  this->options = evaluationOptions;
}


























