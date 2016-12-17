#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPainter>
#include "ContourPlotRenderWidget.h"
#include "scalar_fields.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  auto cbSelectFunction = findChild<QComboBox*>("cbSelectFunction");
  for (unsigned int i = 0; i < obj_funs.size(); i++) {
    cbSelectFunction->addItem(obj_funs[i]->ToString().c_str());
  }
  cbSelectFunction->setCurrentIndex(0);

//  ContourPlotRenderWidget* plot = findChild<ContourPlotRenderWidget*>("plot");
//  Q_ASSERT(plot);
//  QObject::connect(this, &MainWindow::my_signal, plot, &ContourPlotRenderWidget::changeState);
}

MainWindow::~MainWindow()
{
  delete ui;
}

//void MainWindow::my_slot()
//{
//    emit my_signal(10);
//}

void MainWindow::on_cbSelectFunction_currentIndexChanged(int index)
{
  f_cur = obj_funs[index];
  update();
}
