#include "ScalarField.h"

#include <cstdlib>	// size_t
#include <sstream>
#include <exception>
#include <algorithm>	// std::min

#include "DirectionFunction.h"

ScalarField::ScalarField(const std::string& repr, const Domain& domain)
  : repr_(repr), domain_(domain) {}

std::string ScalarField::ToString() const {
  return repr_;
}

Domain ScalarField::GetDomain() const {
  return domain_;
}

Point ScalarField::ShrinkToDomain(const Point& p, const Domain& d) const {
  Point q(p);
  for (unsigned int i = 0; i < p.size(); i++) {
    if (p[i] > d[i][1]) {
      q[i] = d[i][1];
    } else if (p[i] < d[i][0]) {
      q[i] = d[i][0];
    }
  }
  return q;
}

double ScalarField::Eval(const Point& p) const {
  if (GetDomain().Contains(p)) {
    return Eval_(p);
  } else {
    std::stringstream ss;
//    ss << "Cannot evaluate at " << p << ": outside of domain " << GetDomain() << ".";
//    throw std::domain_error(ss.str());
    std::cout << "WARNING: Cannot evaluate at " << p << ": outside of domain "
              << GetDomain() << "; " << "shrinking the vector..." << std::endl;

    return Eval_(ShrinkToDomain(p, GetDomain()));
  }
}

double ScalarField::operator() (const Point& p) {
  return Eval(p);
}

/**
 * @brief Numerically compute the gradient of the scalar field.
 * @param p A point \f\$\mathbf{p} \in \overline{\mathrm{dom}\ f}\$\f.
 */
Point ScalarField::Gradient(const Point& p) const {
  Point g(p.size());
  Point p_plus(p);
  Point p_minus(p);
  auto domain = GetDomain();
  // std::cout << "gradient at " << p << std::endl;
  // std::cout << "domain: " << domain << std::endl;
  // if (!domain.Contains(p)) {
  // std::stringstream ss;
  // ss << "Cannot compute gradient at " << p << ": outside of domain " << domain << ".";
  // throw std::domain_error(ss.str());
  // }
  for (size_t i = 0; i < p.size(); i++) {
    p_plus[i] += std::min(grad_h_, domain[i][1] - p[i]);
    p_minus[i] -= std::min(grad_h_, p[i] - domain[i][0]);
    // if (p_plus[i]
    // std::cout << "p+ = " << p_plus << "; p- = " << p_minus << std::endl;
    // std::cout << "g(p+) = " << Eval(p_plus) << "; g(p-) = " << Eval(p_minus) << std::endl;
    g[i] = (Eval(p_plus) - Eval(p_minus)) / (p_plus[i] - p_minus[i]);
    p_plus[i] = p[i];
    p_minus[i] = p[i];
  }
  return g;
}

double ScalarField::LineSearch(const Point& p, Point& q, double eps) const {
  DirectionFunction phi = DirectionFunction(this, p, q);
  IterResult res = phi.FindMinBisect(0, 1, eps);
  if (res.has_converged) {
    return res.arg[0];
  } else {
    return 0;
  }
}

IterResult ScalarField::FindMin(OptMethod method, MethodParams* params,
                                StopIterCriteria oracle, bool verbose) const {
  IterResult res;
  switch (method) {
    case OptMethod::ConjugateGradient:
      // FIXME: avoid static_cast ?
      res = ConjugateGradient(static_cast<ConjugateGradientParams*>(params),
                              oracle, verbose);
      break;
    case OptMethod::RandomSearchBernoulli:
      res = RandomSearchBernoulli(static_cast<RandomSearchBernoulliParams*>(params),
                                  oracle, verbose);
      break;
  }
  return res;
}

std::ostream& operator<<(std::ostream& s, ScalarField& f) {
  return s << f.ToString();
}
