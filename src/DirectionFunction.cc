#include "DirectionFunction.h"

Point FixDirection(const Point& p, const Point& q, const ScalarField* f) {
  auto dom = f->GetDomain();
  if (! dom.Contains(p)) {
    throw std::domain_error("Domain doesn't contain starting point.");
  }
  Point q_new(q);
  double contract_factor = 0.9;
  while (! dom.Contains(p + q_new)) {
    q_new = contract_factor * q_new;
  }
  return q_new;
}

DirectionFunction::DirectionFunction(const ScalarField* f, const Point& p, const Point& q)
  : Function("", Domain {{0, 1}}),
    p_(p),
    q_(FixDirection(p, q, f)) {
  f_ = f;
}

double DirectionFunction::Eval(const Point& a) const {
  // Skip domain checks -- performed during f->Eval call.
  // std::cout << "eval at alpha = " << a[0] << std::endl; // FIXME
  return Eval_(a[0]);
}

double DirectionFunction::Eval_(double alpha) const {
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
