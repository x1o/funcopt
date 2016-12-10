#ifndef VALDIFFCRITERION_H_
#define VALDIFFCRITERION_H_

#include <cmath>	// std::abs
#include <limits>	// infinity

#include "StopIterCriterion.h"

class ValDiffCriterion : public StopIterCriterion {
private:
	double delta_;
	double f_prev = std::numeric_limits<double>::infinity();

public:
	ValDiffCriterion(double delta) : delta_(delta) {};
	bool ShouldStop(int n_iter, double f_val) {
		// std::cout << f_val << " - " << f_prev << " < " << delta_ << std::endl;
		if (std::abs(f_val - f_prev) < delta_) {
			has_converged = true;
			return true;
		} else {
			f_prev = f_val;
			has_converged = false;
			return false;
		}
	}
};

#endif	// VALDIFFCRITERION_H_
