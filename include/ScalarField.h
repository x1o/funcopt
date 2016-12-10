#ifndef SCALARFIELD_H_
#define SCALARFIELD_H_

#include <string>
#include <ostream>

#include "IterResult.h"
#include "Domain.h"
#include "ConjugateGradient.h"
#include "RandomSearchBernoulli.h"
#include "Point.h"
#include "StopIterCriteria.h"

class ScalarField {
private:
	std::string repr_;
	Domain domain_;
	double grad_h_ = 0.05;
	virtual double Eval_(const Point& p) = 0;

public:
	ScalarField(const std::string& repr, const Domain& domain)
		: repr_(repr), domain_(domain) {};
	const std::string& ToString() {
		return repr_;
	}
	// FIXME: why not const?
	Domain& GetDomain() {
		return domain_;
	}
	virtual double Eval(const Point& p);
	double operator() (const Point& p) {
		return Eval(p);
	}
	Point Gradient(const Point& p);
	// FIXME const function?
	// FIXME make Point const references 
	double LineSearch(Point p, Point q, double eps);
	IterResult FindMin(OptMethod method, MethodParams* params, StopIterCriteria oracle, bool verbose=false);
	IterResult ConjugateGradient(ConjugateGradientParams* params, StopIterCriteria oracle, bool verbose);
	IterResult RandomSearchBernoulli(RandomSearchBernoulliParams* params, StopIterCriteria oracle, bool verbose);
};

std::ostream& operator<<(std::ostream& s, ScalarField& f);

#endif	// SCALARFIELD_H_
