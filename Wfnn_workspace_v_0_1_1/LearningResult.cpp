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


void
LearningResult::viewResult(EvaluatedAgentsGroup* evaluatedAgentsGroup)
{
  this->result = evaluatedAgentsGroup;

  this->ui->nResultsValue->setText(QString::number(result->agents.size()));
  //this->ui->ViewedResultValue->setMaximum(result->agents.size());

  this->ui->nMarks->setText(QString::number(result->agents.at(0)->marks.at(0)));

}
