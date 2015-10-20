#ifndef LEARNINGTAB_H
#define LEARNINGTAB_H

#include <QWidget>

#include "Wfnn/Scenario.h"
#include "Wfnn/Network.h"
#include "Wfnn/EvaluatedAgent.h"


namespace Ui {
class LearningTab;
}

class LearningTab : public QWidget
{
  Q_OBJECT

public:
  explicit LearningTab(QWidget *parent = 0);
  ~LearningTab();


  void setParentWidget(QWidget*);

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

  QWidget* parentWidget;

  void setDefaultValues();
  void makeLearningSession();
  void createResultTab(EvaluatedAgentsGroup* );

};

#endif // LEARNINGTAB_H
