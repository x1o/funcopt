#include "StopIterCriteria.h"

StopIterCriteria::StopIterCriteria(std::initializer_list<StopIterCriterion*> list)
  : criteria_(list) {}

StopIterCriteria::StopIterCriteria(CriteriaList list)
  : criteria_(list) {}

bool StopIterCriteria::HasConverged() const {
  for (size_t i = 0; i < criteria_.size(); i++) {
    if (criteria_[i]->HasConverged()) {
      return true;
    }
  }
  return false;
}

bool StopIterCriteria::ShouldStop(int n_iter, double f_val) const {
  for (size_t i = 0; i < criteria_.size(); i++) {
    if (criteria_[i]->ShouldStop(n_iter, f_val)) {
      return true;
    }
  }
  return false;
}

void StopIterCriteria::AddCriterion(StopIterCriterion* criterion) {
  criteria_.push_back(criterion);
}
