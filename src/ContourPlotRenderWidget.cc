#include "include/ContourPlotRenderWidget.h"
#include <QPainter>
#include <QPolygon>
#include <QPoint>
#include <QColor>
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

void ContourPlotRenderWidget::paintEvent(QPaintEvent*)  {
  QPainter painter(this);
//  QPolygon plot_data(height() * width());
  auto f = [](double x, double y) { return x*x + y*y; };
  double d00, d01, d10, d11;
  d00 = -3;
  d01 = 5;
  d10 = -4;
  d11 = 2;
  double f_val;
  double h = height();
  double w = width();
  std::vector<std::vector<double>> F;
  double dx = (d01 - d00) / w;
  double dy = (d11 - d10) / h;
  double f_min = std::numeric_limits<double>::max();
  double f_max = std::numeric_limits<double>::min();
  for (double y = d11; y >= d10; y -= dy) {
    std::vector<double> row;
    for (double x = d00; x <= d01; x += dx) {
//      f_val = f_cur(Point {x, y});
      f_val = f(x, y);
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
//      std::cout << "(" << i << "," << j << ") : " << "sat = " << satur << std::endl;
//      if (satur < 0) {
//        std::cout << F[j][i] << std::endl;
//      }
      painter.setPen(QColor::fromHsv(240, satur, 255));
      painter.drawPoint(i, j);
    }
//    std::cout << "HI" << std::endl;
  }
//  painter.setPen(QColor("blue"));
//  painter.drawPoint(1, 1);
//  painter.setPen(QColor("red"));
//  painter.drawPoint(20, 20);
//  plot_data[0] = QPoint(1, 1);
//  plot_data[1] = QPoint(10, 10);
//  plot_data[1] = QPoint(20, 20);
//  plot_data[2] = QPoint(30, 30);
  std::cout << width() << " " << height() << std::endl;
//  painter.drawPoints(plot_data);
}

//void ContourPlotRenderWidget::changeState(int i) {
//    state = i;
//    repaint();
//}
