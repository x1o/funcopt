#ifndef MAXITERCRITERION_H_
#define MAXITERCRITERION_H_

#include "StopIterCriterion.h"

class MaxIterCriterion : public StopIterCriterion {
private:
	int max_iter_;

public:
	MaxIterCriterion(int max_iter) : max_iter_(max_iter) {};
	bool ShouldStop(int n_iter, double f_val) {
		// std::cout << n_iter << " >? " << max_iter_ << std::endl;
		if (n_iter > max_iter_) {
			return true;
		} else {
			return false;
		}
	}
};

#endif	// MAXITERCRITERION_H_
