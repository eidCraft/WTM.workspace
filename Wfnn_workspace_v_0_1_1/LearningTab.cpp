#include "LearningTab.h"
#include "ui_LearningTab.h"

#include <QFileDialog>

#include "Wfnn/NetworkManager.h"
#include "Wfnn/ScenarioManager.h"
#include "Wfnn/EvoAgentManager.h"
#include "Wfnn/EvoAgent.h"
#include "Wfnn/Options.h"
#include "Wfnn/EvoController.h"


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
  ui->NeuronsCreatePercentValue->setValue(5.0f);
  ui->NeuronsDeletePercentValue->setValue(5.0f);
  ui->SynapsesDeletePercentValue->setValue(5.0f);
  ui->SynapsesCreatePercentValue->setValue(5.0f);

  ui->MutationOutputValue->setValue(5);
  ui->SelectionOutputValue->setValue(5);

  ui->TimeLimitValue->setValue(3600);
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
  options->setNeuronsDeletePercent(1);
  options->setNeuronsCreatePercent(2);
  options->setSynapsesDeletePercent(1);
  options->setSynapsesCreatePercent(2);
  options->setMutationOutput(5);
  options->setSelectionOutput(1);
  options->setTimeLimit(3600);


  EvoController evoController(options);

  ScenarioManager scenarioManager;

  //Scenario* firstScenario  = scenarioManager.loadFromFile(scenarioFileName.toStdString());
  Scenario* firstScenario  = scenarioManager.loadFromFile(std::string("D:\\Wfnn.data\\Wfnn.1\\Scenario.1.txt"));

  ScenariosSet* scenariosSet = new ScenariosSet();

  scenariosSet->add(firstScenario);


  evoController.evolve(agent, scenariosSet);
}
