#ifndef VALDIFFCRITERION_H_
#define VALDIFFCRITERION_H_

#include <cmath>	// std::abs
#include <limits>	// infinity

#include "StopIterCriterion.h"

class ValDiffCriterion : public StopIterCriterion {
  public:
    ValDiffCriterion(double delta);
    bool ShouldStop(int n_iter, double f_val);

  private:
    double delta_;
    double f_prev = std::numeric_limits<double>::infinity();
};

#endif	// VALDIFFCRITERION_H_
