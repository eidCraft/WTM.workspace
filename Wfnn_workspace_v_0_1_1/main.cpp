#include "MainWindow.h"
#include <QApplication>

#include "LearningTab.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
//fwefwef
  LearningTab learningTab;

  QTabWidget* tabWidget = w.findChild<QTabWidget*>("tabWidget");

  tabWidget->removeTab(0);
  tabWidget->removeTab(0);

  tabWidget->addTab(&learningTab, QString("Crete learning session"));

  return a.exec();
}
