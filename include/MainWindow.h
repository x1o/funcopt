#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "Point.h"
#include "ContourPlotRenderWidget.h"
#include "scalar_fields.h"
#include "GuiConfiguration.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    GuiConfiguration conf_;

    ~MainWindow();

  private slots:
    void on_cbSelectFunction_currentIndexChanged(int index);
    void on_pbMinimize_clicked();
    void on_pbReset_clicked();
    void DisplayPointInStatusBox(Point* p, double val);
    void aboutBox();

  signals:

  private:
    Ui::MainWindow *ui;
    ScalarFieldList obj_funs_;
};

#endif // MAINWINDOW_H
