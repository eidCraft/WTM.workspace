#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T16:07:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wfnn_workspace_v_0_1_1
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Wfnn/EvaluatedAgent.cpp \
    Wfnn/EvoAgent.cpp \
    Wfnn/EvoAgentManager.cpp \
    Wfnn/EvoController.cpp \
    Wfnn/Genom.cpp \
    Wfnn/GenomManager.cpp \
    Wfnn/MutationController.cpp \
    Wfnn/Network.cpp \
    Wfnn/NetworkManager.cpp \
    Wfnn/Neuron.cpp \
    Wfnn/Options.cpp \
    Wfnn/Scenario.cpp \
    Wfnn/ScenarioManager.cpp \
    Wfnn/SelectionArbiter.cpp \
    Wfnn/SelectionController.cpp \
    Wfnn/SelectionEvaluator.cpp \
    Wfnn/SimulationController.cpp \
    Wfnn/TestedAgent.cpp \
    LearningTab.cpp \
    LearningResult.cpp \
    Wfnn/EvoResult.cpp

HEADERS  += MainWindow.h \
    Wfnn/EvaluatedAgent.h \
    Wfnn/EvoAgent.h \
    Wfnn/EvoAgentManager.h \
    Wfnn/EvoController.h \
    Wfnn/Genom.h \
    Wfnn/GenomManager.h \
    Wfnn/MutationController.h \
    Wfnn/Network.h \
    Wfnn/NetworkManager.h \
    Wfnn/Neuron.h \
    Wfnn/Options.h \
    Wfnn/Scenario.h \
    Wfnn/ScenarioManager.h \
    Wfnn/SelectionArbiter.h \
    Wfnn/SelectionController.h \
    Wfnn/SelectionEvaluator.h \
    Wfnn/SimulationController.h \
    Wfnn/TestedAgent.h \
    LearningTab.h \
    LearningResult.h \
    Wfnn/EvoResult.h

FORMS    += MainWindow.ui \
    LearningTab.ui \
    LearningResult.ui
