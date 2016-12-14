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
  public:
    ScalarField(const std::string& repr, const Domain& domain);
    std::string ToString() const;
    Domain GetDomain() const;
    virtual double Eval(const Point& p) const;
    double operator() (const Point& p);
    Point Gradient(const Point& p) const;
    // FIXME make Point const references
    double LineSearch(const Point& p, const Point& q, double eps) const;
    IterResult FindMin(OptMethod method, MethodParams* params,
                       StopIterCriteria oracle, bool verbose=false) const;
    IterResult ConjugateGradient(ConjugateGradientParams* params,
                                 StopIterCriteria oracle, bool verbose) const;
    IterResult RandomSearchBernoulli(RandomSearchBernoulliParams* params,
                                     StopIterCriteria oracle, bool verbose) const;

  private:
    std::string repr_;
    Domain domain_;
    const double grad_h_ = 0.001;
    virtual double Eval_(const Point& p) const = 0;
};

std::ostream& operator<<(std::ostream& s, ScalarField& f);

#endif	// SCALARFIELD_H_
