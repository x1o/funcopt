#ifndef MAXITERCRITERION_H_
#define MAXITERCRITERION_H_

#include "StopIterCriterion.h"

class MaxIterCriterion : public StopIterCriterion {
  private:
    int max_iter_;

  public:
    MaxIterCriterion(int max_iter);
    bool ShouldStop(int n_iter, double f_val);
};

#endif	// MAXITERCRITERION_H_
