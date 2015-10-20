#ifndef LEARNINGTAB_H
#define LEARNINGTAB_H

#include <QWidget>

#include "Wfnn/Scenario.h"
#include "Wfnn/Network.h"

namespace Ui {
class LearningTab;
}

class LearningTab : public QWidget
{
  Q_OBJECT

public:
  explicit LearningTab(QWidget *parent = 0);
  ~LearningTab();

private slots:
 void handleNetworkFileLoadButton();
 void handleScenarioFileLoadButton();
 void handleLearnButton();

private:
  Ui::LearningTab *ui;

  QString networkFileName;
  QString scenarioFileName;

  Scenario scenario;
  Network network;

  void setDefaultValues();
  void makeLearningSession();
};

#endif // LEARNINGTAB_H
