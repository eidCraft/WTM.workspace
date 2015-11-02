#include "LearningTab.h"
#include "ui_LearningTab.h"

#include <QFileDialog>

#include "LearningResult.h"

#include "Wfnn/NetworkManager.h"
#include "Wfnn/ScenarioManager.h"
#include "Wfnn/EvoAgentManager.h"
#include "Wfnn/EvoAgent.h"
#include "Wfnn/Options.h"
#include "Wfnn/EvoController.h"
#include "Wfnn/EvaluatedAgent.h"


LearningTab::~LearningTab()
{
  delete ui;
}

LearningTab::LearningTab(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LearningTab)
{
  ui->setupUi(this);

    connect(ui->NetworkFileLoad, SIGNAL (released()), this, SLOT (handleNetworkFileLoadButton()));
    connect(ui->ScenarioFileLoad, SIGNAL (released()), this, SLOT (handleScenarioFileLoadButton()));
    connect(ui->Learn, SIGNAL (released()), this, SLOT (handleLearnButton()));

  setDefaultValues();
}

void
LearningTab::setDefaultValues()
{
  ui->NeuronsCreatePercentValue->setValue(10.0f);
  ui->NeuronsDeletePercentValue->setValue(10.0f);
  ui->SynapsesDeletePercentValue->setValue(10.0f);
  ui->SynapsesCreatePercentValue->setValue(10.0f);

  ui->MutationOutputValue->setValue(10);
  ui->SelectionOutputValue->setValue(5);

  ui->EpochsLimitValue->setValue(50);
}

void
LearningTab::handleNetworkFileLoadButton()
{
   networkFileName = QFileDialog::getOpenFileName(this,
      tr("Open network"), "/", tr("TXT files(*.txt)"));

  ui->NetworkFileText->setText(networkFileName);

  // check file for compability

  // load network
}

void
LearningTab::handleScenarioFileLoadButton()
{
  scenarioFileName = QFileDialog::getOpenFileName(this,
     tr("Open scenario"), "/", tr("TXT files(*.txt)"));

  ui->ScenarioFileText->setText(scenarioFileName);

  // check file for compability
}

void
LearningTab::handleLearnButton()
{
  makeLearningSession();

}

void
LearningTab::makeLearningSession()
{
  EvoAgentManager agentManager;

  //EvoAgent* agent = agentManager.load(networkFileName.toStdString());
  EvoAgent* agent = agentManager.load(std::string("D:\\Wfnn.data\\Wfnn.1\\Network.txt"));

  EvoOptions* options = new EvoOptions();
  options->setNeuronsDeletePercent(ui->NeuronsDeletePercentValue->value());
  options->setNeuronsCreatePercent(ui->NeuronsCreatePercentValue->value());
  options->setSynapsesDeletePercent(ui->SynapsesDeletePercentValue->value());
  options->setSynapsesCreatePercent(ui->SynapsesCreatePercentValue->value());
  options->setMutationOutput(ui->MutationOutputValue->value());
  options->setSelectionOutput(ui->SelectionOutputValue->value());
  options->setEpochsLimit(ui->EpochsLimitValue->value());
  options->setEvolutionAccurency(50.0f);

  EvoController evoController(options);

  ScenarioManager scenarioManager;

  //Scenario* firstScenario  = scenarioManager.loadFromFile(scenarioFileName.toStdString());
  Scenario* firstScenario  = scenarioManager.loadFromFile(std::string("D:\\Wfnn.data\\Wfnn.1\\Scenario.1.txt"));

  ScenariosSet* scenariosSet = new ScenariosSet();

  scenariosSet->add(firstScenario);

  EvaluatedAgentsGroup* resultingAgents;
  resultingAgents = evoController.evolve(agent, scenariosSet);

   createResultTab(resultingAgents);
}


void
LearningTab::createResultTab(EvaluatedAgentsGroup* resultingAgents)
{
  LearningResult* learningResult = new LearningResult();


  learningResult->viewResult(resultingAgents);
  //QObject* parent = this->parentWidget();

  //((QTabWidget*)parent)->addTab(learningResult, QString("Create learning session"));
  ((QTabWidget*)parentWidget)->addTab(learningResult, QString("Create learning session"));

}

void
LearningTab::setParentWidget(QWidget* parentWidget)
{
  this->parentWidget = parentWidget;
}
