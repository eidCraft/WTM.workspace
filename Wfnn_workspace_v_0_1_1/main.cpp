#include "MainWindow.h"
#include <QApplication>

#include "LearningTab.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
//fwefwef



  QTabWidget* tabWidget = w.findChild<QTabWidget*>("tabWidget");

  tabWidget->removeTab(0);
  tabWidget->removeTab(0);

  LearningTab learningTab;
  learningTab.setParentWidget(tabWidget);


  tabWidget->addTab(&learningTab, QString("Create learning session"));

  return a.exec();
}
