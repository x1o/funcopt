#ifndef DIRECTIONFUNCTION_H_
#define DIRECTIONFUNCTION_H_

#include "Function.h"

#include <cmath>      // abs()
#include <algorithm>  // min()
#include <iostream>   // FIXME

#include "Domain.h"
#include "Point.h"
#include "ScalarField.h"

class DirectionFunction : public Function {
  public:
    // FIXME: const, Point&
    // FIXME: proper repr
    // FIXME: don't compute L2Norm() twice
    DirectionFunction(const ScalarField *f, const Point& p, const Point& q);
    double Eval(const Point& a) const;

  private:
    const ScalarField* f_;
    Point p_, q_;

    double Eval_(double alpha) const;
};

#endif	// DIRECTIONFUNCTION_H_
