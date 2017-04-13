#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ContourPlotRenderWidget.h"
#include <string>
#include <QPainter>
#include <QMessageBox>
#include "MaxIterCriterion.h"
#include "ValDiffCriterion.h"
#include "scalar_fields.h"
#include "OptMethods.h"
#include "ConjugateGradient.h"
#include "RandomSearchBernoulli.h"
#include "IterResult.h"
#include <iostream>
#include <exception>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    conf_(),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  obj_funs_ = { new F1(), new F2(), new F3() };

  ContourPlotRenderWidget* plot = findChild<ContourPlotRenderWidget*>("plot");
  plot->SetConfig(&conf_);

  findChild<QDoubleSpinBox*>("sbValDiff")->setMinimum(10e-10);

  connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
  connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::aboutBox);

  auto cbSelectFunction = findChild<QComboBox*>("cbSelectFunction");
  std::string f_repr;
  for (unsigned int i = 0; i < obj_funs_.size(); i++) {
    f_repr = obj_funs_[i]->ToString() + " on "
             + obj_funs_[i]->GetDomain().ToString();
    cbSelectFunction->addItem(f_repr.c_str());
  }
  cbSelectFunction->setCurrentIndex(0);

  QObject::connect(plot, &ContourPlotRenderWidget::CurrentPointChanged,
                   this, &MainWindow::DisplayPointInStatusBox);

//  Q_ASSERT(plot);
  // TODO: "Draw only successful steps" checkbox for RandomSearch.
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_cbSelectFunction_currentIndexChanged(int index)
{
  conf_.SetCurrentFunc(obj_funs_[index]);
  conf_.SetInitialPoint(nullptr);
  conf_.has_run = false;
  update();
}

void MainWindow::on_pbMinimize_clicked()
{
  if (conf_.GetInitialPoint() == nullptr) {
    QMessageBox::warning(this,
                         "No initial point selected",
                         "Please select the initial point first by clicking on the contour plot.");
//    QMessageBox msg_box;
//    msg_box.setText("Initial point hasn't been selected.");
//    msg_box.setInformativeText(
//          );
//    msg_box.exec();
    return;
  }
  CriteriaList criteria;
  if (findChild<QCheckBox*>("chbMaxIter")->isChecked()) {
    criteria.push_back(new MaxIterCriterion(
                         findChild<QSpinBox*>("sbMaxIter")->value()));
  }
  if (findChild<QCheckBox*>("chbValDiff")->isChecked()) {
    criteria.push_back(new ValDiffCriterion(
                         findChild<QDoubleSpinBox*>("sbValDiff")->value()));
  }
  if (criteria.size() == 0) {
    QMessageBox::warning(this,
                         "No stop iteration criterion specified",
                         "Please specify at least one stop iteration criterion.");
    return;
  }
  // TODO: delete criteria?
  StopIterCriteria oracle(criteria);

  IterResult res;
  ConjugateGradientParams cg_params;
  RandomSearchBernoulliParams rs_params;
  switch (findChild<QToolBox*>("tbOptMethod")->currentIndex()) {
    case 0:
      cg_params.x_0 = Point(*(conf_.GetInitialPoint()));
      res = conf_.GetCurrentFunc()->FindMin(OptMethod::ConjugateGradient,
                                            &cg_params, oracle, true);
      break;
    case 1:
      rs_params.x_0 = Point(*(conf_.GetInitialPoint()));
      rs_params.global_search_prob = findChild<QDoubleSpinBox*>("sbGlobSearchProb")->value();
      rs_params.contract_factor = findChild<QDoubleSpinBox*>("sbContractFactor")->value();
      res = conf_.GetCurrentFunc()->FindMin(OptMethod::RandomSearchBernoulli,
                                            &rs_params, oracle, true);
      break;
    default:
      throw std::invalid_argument("Unsupported method");	// Shouldn't happen
  }

  findChild<QLabel*>("lab_min")->setText(QString::number(res.val));
  findChild<QLabel*>("lab_argmin")->setText(res.arg.ToString().c_str());
  findChild<QLabel*>("lab_n_iter")->setText(QString::number(res.n_iter));

//  std::cout << "argmin = " << res.arg << std::endl;
//  std::cout << "min = " << res.val << std::endl;
//  if (res.has_converged) {
//    std::cout << "Converged in ";
//  } else {
//    std::cout << "Couldn't converge after ";
//  }
//  std::cout << res.n_iter << " iterations." << std::endl;

  conf_.has_run = true;
  conf_.SetIterResult(res);
  update();
}

void MainWindow::on_pbReset_clicked()
{
  conf_.SetInitialPoint(nullptr);
  conf_.has_run = false;
  update();
}

void MainWindow::DisplayPointInStatusBox(Point* p, double val)
{
  std::stringstream ss;
  ss << "f(" << *p << ") = " << val;
  statusBar()->showMessage(QString(ss.str().c_str()));
  delete p;
}

void MainWindow::aboutBox()
{
  QMessageBox::about(this, "Function optimization", "(c) xio 2016");
}
