#include "LearningResult.h"
#include "ui_LearningResult.h"

LearningResult::LearningResult(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LearningResult)
{
  ui->setupUi(this);
}
///sdf
LearningResult::~LearningResult()
{
  delete ui;
}

LearningResult::LearningResult(EvaluatedAgentsGroup* evaluatedAgentsGroup)
{
 evaluatedAgentsGroup->agents[0]-> ;
}
