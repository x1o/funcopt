#ifndef CONTOURPLOTRENDERWIDGET_H
#define CONTOURPLOTRENDERWIDGET_H

#include <QWidget>

class ContourPlotRenderWidget : public QWidget
{
    Q_OBJECT
//    int state;
  public:
//    virtual void paintEvent(QPaintEvent*);
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    explicit ContourPlotRenderWidget(QWidget *parent = 0);

  signals:

  public slots:
//    void changeState(int x);
};

#endif // CONTOURPLOTRENDERWIDGET_H
