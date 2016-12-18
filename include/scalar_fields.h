#ifndef SCALAR_FIELDS_H_
#define SCALAR_FIELDS_H_

#include <cmath>		// pow(), exp()
#include <vector>

#include "Point.h"
#include "Domain.h"
#include "ScalarField.h"

class F1 : public ScalarField {
  private:
    double Eval_(const Point& p) const {
      return pow(p[0], 2) + pow(p[1], 2);
    }

  public:
    F1() : ScalarField("x^2 + y^2", Domain {{-3, 5}, {-4, 2}}) {}
};

class F2 : public ScalarField {
  private:
    double Eval_(const Point& p) const {
      return pow(p[0] - 70, 2) + 100 * pow(p[0] - p[1], 2);
    }

  public:
    F2() : ScalarField("(x-70)^2 + 100*(x-y)^2",
                       Domain {{-100, 100}, {-100, 100}}) {}
};


class F3 : public ScalarField {
  private:
    double Eval_(const Point& p) const {
      return sin(10*p[0]*p[0] + p[1]) + p[1]*p[1] * exp(fabs(p[0]+p[1]));
    }

  public:
    F3() : ScalarField("sin(10*x^2 + y) + y^2*exp(|x + y|)",
                       Domain {{-3, 3}, {-2, 2}}) {}
};

class F4 : public ScalarField {
  private:
    double Eval_(const Point& p) const {
      return pow(p[0]*p[0] - p[1], 2) + pow(p[0] - p[1], 2) + sin(p[2]);
    }

  public:
    F4() : ScalarField("(x^2 - y)^2 + (x - y)^2 + sin(z)",
                       Domain {{-10, 10}, {-10, 10}, {-10, 10}}) {}
};

class F5 : public ScalarField {
  private:
    double Eval_(const Point& p) const {
      return pow(p[0]*p[0] - p[1], 2) + pow(p[0] - 1, 2) + pow(p[2] - p[1], 2);
    }

  public:
    F5() : ScalarField("(x^2 - y)^2 + (x - 1)^2 + (z - y)^2",
                       Domain {{-40, 30}, {-10, 78}, {0, 15}}) {}
};

typedef std::vector<ScalarField*> ScalarFieldList;

const ScalarFieldList all_scalar_fields = { new F1(), new F2(), new F3(),
                                            new F4(), new F5() };


#endif	// SCALAR_FIELDS_H_
