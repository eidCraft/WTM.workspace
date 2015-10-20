#ifndef LEARNINGRESULT_H
#define LEARNINGRESULT_H

#include <QWidget>

namespace Ui {
class LearningResult;
}

class LearningResult : public QWidget
{
  Q_OBJECT

public:
  explicit LearningResult(QWidget *parent = 0);
  ~LearningResult();

private:
  Ui::LearningResult *ui;
};

#endif // LEARNINGRESULT_H
