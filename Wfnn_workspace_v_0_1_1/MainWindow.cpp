#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  //ui->tabWidget
}

MainWindow::~MainWindow()
{
  delete ui;
}

void
MainWindow::resizeEvent(QResizeEvent* event)// resizeEvent(QResizeEvent* event)
{

  QMainWindow::resizeEvent(event);

  ui->tabWidget->setGeometry (0, 0, width() + 1, height() + 1);
}
