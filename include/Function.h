#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>	// FIXME
#include <string>

#include "IterResult.h"
#include "Point.h"
#include "Domain.h"
#include "ScalarField.h"

class Function : public ScalarField {
  public:
    Function(const std::string& repr, const Domain& domain);
    double Eval(double r) const;
    double operator()(double r);
    double Derivative(double x) const;
    // TODO: FindRootBisect and feed with Derivative() or Eval()
    IterResult FindMinBisect(double a, double b, double eps) const;

  private:
    double Eval_(const Point& p) const;
    virtual double Eval_(double r) const = 0;
};

#endif	// FUNCTION_H_
