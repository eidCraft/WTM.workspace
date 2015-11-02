#ifndef LEARNINGRESULT_H
#define LEARNINGRESULT_H

#include <QWidget>

#include "Wfnn/EvaluatedAgent.h"


namespace Ui {
class LearningResult;
}

class LearningResult : public QWidget
{
  Q_OBJECT

public:
  explicit LearningResult(QWidget *parent = 0);
  ~LearningResult();

  EvaluatedAgentsGroup* result;

  void viewResult(EvaluatedAgentsGroup*);

  void handleViewedResultValue(int);
  void refreshView(int);

private:
  Ui::LearningResult *ui;
};







#endif // LEARNINGRESULT_H
