#include "LearningResult.h"
#include "ui_LearningResult.h"

LearningResult::LearningResult(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LearningResult)
{
  ui->setupUi(this);

  connect(ui->ViewedResultValue, SIGNAL(valueChanged(int)), this, SLOT (handleViewedResultValue(int)));
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
  this->ui->ViewedResultValue->setMaximum(result->agents.size());
//ui->ViewedResultValue->va
  refreshView(0);
}

void
LearningResult::refreshView(int newValue)
{
  //this->ui->Mark->setText(QString::number(result->agents.at(ui->ViewedResultValue->value())->marks.at(0)));
  this->ui->Mark->setText(QString::number(result->agents.at(newValue)->totalMark));
  this->ui->MaximumMark->setText(QString::number(result->agents.at(newValue)->scenarios->maximumMark));
  //this->ui->Mark->setText(QString::number(newValue));
}

void
LearningResult::handleViewedResultValue(int newValue)
{
  refreshView(newValue);
}
