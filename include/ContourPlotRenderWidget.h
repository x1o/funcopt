#ifndef CONTOURPLOTRENDERWIDGET_H
#define CONTOURPLOTRENDERWIDGET_H

#include <QWidget>
#include "GuiConfiguration.h"

class ContourPlotRenderWidget : public QWidget
{
    Q_OBJECT
//    int state;
  public:
    explicit ContourPlotRenderWidget(QWidget *parent = 0);
    void SetConfig(GuiConfiguration* conf);

  protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

  signals:
    void CurrentPointChanged(Point* p, double val);

  public slots:

  private:
    void DrawPlot(ScalarField* f);
    void DrawX(const QPoint& p);
    void DrawTrace(const std::vector<Point>& trace);
    GuiConfiguration* conf_;
    QPoint R2ToScreen(const Point& p);
    Point* ScreenToR2(const QPoint& p);
};

#endif // CONTOURPLOTRENDERWIDGET_H
