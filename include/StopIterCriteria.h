#ifndef STOPITERCRITERIA_H_
#define STOPITERCRITERIA_H_

#include <cstdlib>	// size_t
#include <vector>

#include "StopIterCriterion.h"

// Any way not to deal with pointers?
typedef std::vector<StopIterCriterion*> CriteriaList;

class StopIterCriteria {
private:
	CriteriaList criteria_;

public:
	StopIterCriteria(std::initializer_list<StopIterCriterion*> list) : criteria_(list) {};
	bool HasConverged() {
		for (size_t i = 0; i < criteria_.size(); i++) {
			if (criteria_[i]->HasConverged()) {
				return true;
			}
		}
		return false;
	}
	bool ShouldStop(int n_iter, double f_val) {
		for (size_t i = 0; i < criteria_.size(); i++) {
			if (criteria_[i]->ShouldStop(n_iter, f_val)) {
				return true;
			}
		}
		return false;
	}
	// FIXME: const, &
	void AddCriterion(StopIterCriterion* criterion) {
		criteria_.push_back(criterion);
	}
};

#endif	// STOPITERCRITERIA_H_
