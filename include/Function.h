#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>	// FIXME
#include <string>

#include "IterResult.h"
#include "Point.h"
#include "Domain.h"
#include "ScalarField.h"

class Function : public ScalarField {
private:
	double Eval_(const Point& p) {
		return Eval_(p[0]);
	}
	virtual double Eval_(double r) = 0;

public:
	Function(const std::string& repr, const Domain& domain)
		: ScalarField(repr, domain) {};
	double Eval(double r) {
		// std::cout << "f eval at " << r << std::endl; // FIXME
		return ScalarField::Eval(Point {r});
	}
	double operator()(double r) {
		return Eval(r);
	}
	double Derivative(double x) {
		// std::cout << "deriv" << std::endl; // FIXME
		return Gradient(Point {x})[0];
	}
	// TODO: FindRootBisect and feed with Derivative() or Eval()
	IterResult FindMinBisect(double a, double b, double eps);
};

#endif	// FUNCTION_H_
