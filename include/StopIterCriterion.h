#ifndef STOPITERCRITERION_H_
#define STOPITERCRITERION_H_

class StopIterCriterion {
protected:
	bool has_converged = false;

public:
	bool HasConverged() {
		return has_converged;
	};
	virtual bool ShouldStop(int n_iter, double f_val) = 0;
};

#endif	// STOPITERCRITERION_H_
