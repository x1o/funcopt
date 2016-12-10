#ifndef DIRECTIONFUNCTION_H_
#define DIRECTIONFUNCTION_H_

#include "Function.h"

#include <cmath>      // abs()
#include <algorithm>  // min()
#include <iostream>	// FIXME

#include "Domain.h"
#include "Point.h"
#include "ScalarField.h"

class DirectionFunction : public Function {
private:
	ScalarField* f_;
	Point p_, q_;
	double Eval_(double alpha) {
    Point x = p_ + alpha * q_;
    auto dom = f_->GetDomain();
    // FIXME: ugly
    for (size_t i = 0; i < x.size(); i++) {
      for (size_t j = 0; j < 2; j++) {
        if (std::abs(x[i]) > std::abs(dom[i][j])) {
          std::cout << "WARNING: shrinking argument vector for direction function: x[" << i << "][" << j << "] = " << x[i] << " -> " << dom[i][j] << std::endl;
          x[i] = dom[i][j];
        }
      }
    }
    // std::cout << "f(" << x << ")" << std::endl;
		return f_->Eval(x);
	}
public:
	// FIXME: const, Point&
	// FIXME: proper repr
	// FIXME: don't compute L2Norm() twice
	DirectionFunction(ScalarField *f, const Point& p, const Point& q)
		// : Function("", Domain {{-std::min((f->GetDomain() - p) / q),
                            // std::min((f->GetDomain() - p) / q)}}),
		: Function("", Domain {{-q.L2Norm(), q.L2Norm()}}),
		  p_(p),
		  q_(q) {
		f_ = f;
	}
	double Eval(const Point& a) {
		// Skip domain checks -- performed during f->Eval call.
		// std::cout << "eval at alpha = " << a[0] << std::endl; // FIXME
		return Eval_(a[0]);
	}
};

#endif	// DIRECTIONFUNCTION_H_
