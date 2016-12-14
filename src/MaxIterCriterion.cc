#include "MaxIterCriterion.h"

MaxIterCriterion::MaxIterCriterion(int max_iter) : max_iter_(max_iter) {}

bool MaxIterCriterion::ShouldStop(int n_iter, double f_val) {
  // std::cout << n_iter << " >? " << max_iter_ << std::endl;
  if (n_iter > max_iter_) {
    return true;
  } else {
    return false;
  }
}
