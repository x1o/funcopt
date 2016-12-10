#include "Function.h"

#include <iostream> //FIXME

#include <cmath>	// std::abs

IterResult Function::FindMinBisect(double a, double b, double eps) {
	double c, y, z;
	unsigned int n_iter = 0;
	IterResult res;

	y = Derivative(a);
	z = Derivative(b);

	// std::cout << "a = " << a << ", b = " << b << std::endl;
	// std::cout << "y = " << y << ", z = " << z << std::endl;

	// f is assumed to be strictly monotone
	if (z * y > 0) {
		res.has_converged = false;
		res.arg = Point {};
		res.val = 0;
		res.n_iter = 0;
		return res;
	}

	if (std::abs(y) < eps) {
		res.has_converged = true;
		res.arg = Point {a};
		res.val = Eval(y);
		res.n_iter = n_iter;
		return res;
	}

	if (std::abs(z) < eps) {
    std::cout << "OOPS" << std::endl;
		res.has_converged = true;
		res.arg = Point {b};
		res.val = Eval(z);
		res.n_iter = n_iter;
		return res;
	}

	while (z > 0 or (b - a) > eps) {
		c = (a + b) / 2;
		z = Derivative(c);
		if (z * y >= 0)
			a = c;
		else
			b = c;
		n_iter++;
	}

	res.has_converged = true;
	res.arg = Point {c};
	res.val = Eval(c);
	res.n_iter = n_iter;

	return res;
}
