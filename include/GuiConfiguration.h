#ifndef GUICONFIGURATION_H
#define GUICONFIGURATION_H

#include "ScalarField.h"
#include "Point.h"
#include <QPoint>


class GuiConfiguration
{
  public:
    GuiConfiguration();
    ScalarField* GetCurrentFunc() const;
    void SetCurrentFunc(ScalarField* f);
    Point* GetInitialPoint() const;
    void SetInitialPoint(Point* x_0);
    IterResult& GetIterResult();
    void SetIterResult(const IterResult& res);
    // FIXME: res_ should be initialized to nullptr
    // Currently FindMind in MainWindow returns IterResult, not a pointer
    // How to make the object live after the method in which it was created returns?
    bool has_run = false;

//  signals:

//  public slots:

  private:
    ScalarField* f_cur_;
    Point* x_0_;
    IterResult res_;
};

#endif // GUICONFIGURATION_H
