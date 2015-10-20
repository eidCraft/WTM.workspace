#include "LearningResult.h"
#include "ui_LearningResult.h"

LearningResult::LearningResult(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LearningResult)
{
  ui->setupUi(this);
}

LearningResult::~LearningResult()
{
  delete ui;
}
