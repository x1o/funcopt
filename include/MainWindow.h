#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "ContourPlotRenderWidget.h"
#include "scalar_fields.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:
//    void my_slot();

    void on_cbSelectFunction_currentIndexChanged(int index);

  signals:
//    void my_signal(int i);

  private:
    Ui::MainWindow *ui;
    const ScalarFieldList obj_funs = { new F1(), new F2(), new F3() };
    ScalarField* f_cur;
};

#endif // MAINWINDOW_H
