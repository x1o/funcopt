#include "ValDiffCriterion.h"

ValDiffCriterion::ValDiffCriterion(double delta) : delta_(delta) {}

bool ValDiffCriterion::ShouldStop(int n_iter, double f_val) {
  // std::cout << f_val << " - " << f_prev << " < " << delta_ << std::endl;
  if (std::abs(f_val - f_prev) < delta_) {
    has_converged_ = true;
    return true;
  } else {
    f_prev = f_val;
    has_converged_ = false;
    return false;
  }
}
