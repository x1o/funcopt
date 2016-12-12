#ifndef STOPITERCRITERIA_H_
#define STOPITERCRITERIA_H_

#include <cstdlib>	// size_t
#include <vector>

#include "StopIterCriterion.h"

// Any way not to deal with pointers?
typedef std::vector<StopIterCriterion*> CriteriaList;

/**
 * @brief A set of StopIterCriterion() instances.
 *
 * If at least one StopIterCriterion() decides that the method should stop or
 * has already converged, so is the final decision.
 */
class StopIterCriteria {
  public:
    StopIterCriteria(std::initializer_list<StopIterCriterion*> list);
    bool HasConverged() const;
    bool ShouldStop(int n_iter, double f_val) const;
    void AddCriterion(StopIterCriterion* criterion);

  private:
    CriteriaList criteria_;
};

#endif	// STOPITERCRITERIA_H_
