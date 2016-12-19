#include "include/ContourPlotRenderWidget.h"
#include <QPainter>
#include <QPolygon>
#include <QPoint>
#include <QColor>
#include <QMouseEvent>
#include <iostream>
#include <vector>
#include <limits>
#include "Point.h"
#include <cmath>  // floor

ContourPlotRenderWidget::ContourPlotRenderWidget(QWidget *parent)
  : QWidget(parent)
{
  // FIXME: wider default plot area
  // resize(1000, 900);
}

void ContourPlotRenderWidget::SetConfig(GuiConfiguration* conf)
{
  conf_ = conf;
}

void ContourPlotRenderWidget::DrawPlot(ScalarField* f)
{
  QPainter painter(this);
//  auto f = [](double x, double y) { return x*x + y*y; };
  double dom_0_L, dom_0_R, dom_1_L, dom_1_R;
  dom_0_L = f->GetDomain()[0][0];
  dom_0_R = f->GetDomain()[0][1];
  dom_1_L = f->GetDomain()[1][0];
  dom_1_R = f->GetDomain()[1][1];
  double f_val;
  double h = height();
  double w = width();
  std::vector<std::vector<double>> F;
  double dx = (dom_0_R - dom_0_L) / w;
  double dy = (dom_1_R - dom_1_L) / h;
  double f_min = std::numeric_limits<double>::max();
  double f_max = std::numeric_limits<double>::min();
  for (double y = dom_1_R; y >= dom_1_L; y -= dy) {
    std::vector<double> row;
    for (double x = dom_0_L; x <= dom_0_R; x += dx) {
      f_val = (*f)(Point {x, y});
//      f_val = f(x, y);
      if (f_val < f_min) {
        f_min = f_val;
      }
      if (f_val > f_max) {
        f_max = f_val;
      }
      row.push_back(f_val);
//      std::cout << f_val << " ";
    }
    F.push_back(row);
  }
  int n_levels = 20;
  int dsat = 255 / n_levels;
  double f_range = f_max - f_min;
  double satur;
//  std::cout << "f: from " << f_min << " to " << f_max << std::endl;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      satur = std::floor((F[j][i] - f_min) / f_range * n_levels) * dsat;
      painter.setPen(QColor::fromHsv(240, satur, 255));
      painter.drawPoint(i, j);
    }
  }
  //  std::cout << width() << " " << height() << std::endl;
}

void ContourPlotRenderWidget::DrawX(const QPoint& p)
{
  QPainter painter(this);
  painter.drawLine(p.x() - 4, p.y() - 4, p.x() + 3, p.y() + 3);
  painter.drawLine(p.x() - 4, p.y() + 4, p.x() + 3, p.y() - 3);
}

void ContourPlotRenderWidget::DrawTrace(const std::vector<Point>& trace)
{
  QPainter painter(this);
  QPoint q_prev;
  QPoint q;
  painter.setBrush(QBrush(QColor("black")));
  for (unsigned int i = 0; i < trace.size(); i++) {
    if (i == trace.size() - 1) {
      painter.setPen(QColor("red"));
      painter.setBrush(QBrush(QColor("red")));
    } else {
      painter.setPen(QColor("black"));
    }
    q = QPoint(R2ToScreen(trace[i]));
    painter.drawEllipse(q, 2, 2);
    if (i != 0) {
      painter.setPen(QColor("grey"));
      painter.drawLine(q_prev, q);
    }
    q_prev = q;
  }
}

QPoint ContourPlotRenderWidget::R2ToScreen(const Point& p)
{
  auto f = conf_->GetCurrentFunc();
  double dom_0_L = f->GetDomain()[0][0];
  double dom_0_R = f->GetDomain()[0][1];
  double dom_1_L = f->GetDomain()[1][0];
  double dom_1_R = f->GetDomain()[1][1];
  double dx = (dom_0_R - dom_0_L) / width();
  double dy = (dom_1_R - dom_1_L) / height();
  return QPoint(std::floor((p[0] - dom_0_L) / dx),
                std::floor((-p[1] + dom_1_R) / dy));
}

Point* ContourPlotRenderWidget::ScreenToR2(const QPoint& p)
{
  auto f = conf_->GetCurrentFunc();
  double dom_0_L = f->GetDomain()[0][0];
  double dom_0_R = f->GetDomain()[0][1];
  double dom_1_L = f->GetDomain()[1][0];
  double dom_1_R = f->GetDomain()[1][1];
  double dx = (dom_0_R - dom_0_L) / width();
  double dy = (dom_1_R - dom_1_L) / height();
  return new Point {p.x()*dx + dom_0_L, - p.y()*dy + dom_1_R};
}

void ContourPlotRenderWidget::paintEvent(QPaintEvent*)
{
  DrawPlot(conf_->GetCurrentFunc());
  auto x_0 = conf_->GetInitialPoint();
  if (x_0 != nullptr) {
    DrawX(R2ToScreen(*x_0));
  }
  auto& res = conf_->GetIterResult();
  if (conf_->has_run) {
    DrawTrace(res.trace);
  }
}

void ContourPlotRenderWidget::mousePressEvent(QMouseEvent* event)
{
  if (!(event->button() == Qt::LeftButton)) {
    return;
  }
//  std::cout << event->pos().x() << " " << event->pos().y() << " -> ";
  conf_->SetInitialPoint(ScreenToR2(event->pos()));
//  std::cout << "x_0 = " << *(conf_->GetInitialPoint()) << "; w = " << width() << ", h = " << height() << std::endl;
  update();
//  repaint();
}

void ContourPlotRenderWidget::mouseMoveEvent(QMouseEvent* event)
{
  Point* x_ptr = ScreenToR2(event->pos());
  emit CurrentPointChanged(x_ptr, conf_->GetCurrentFunc()->Eval(*x_ptr));
}
