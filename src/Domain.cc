#include "Domain.h"

#include <cstdlib>	// size_t
#include <limits>	// epsilon

const double eps = std::numeric_limits<double>::epsilon();

Domain::Domain(std::initializer_list<Point> d) : std::vector<Point>(d) {}

bool Domain::Contains(const Point& p) const {
  for (size_t i = 0; i < p.size(); i++) {
    // FIXME: 10*eps??
    if ((p[i] < ((*this)[i][0] - 10*eps)) or (p[i] > ((*this)[i][1] + 10*eps))) {
      return false;
    }
  }
  return true;
}

void Domain::ZoomToPoint(Domain& dom_target, const Point& p, double contract_factor) const {
  double lim_left, lim_right;
  for (size_t axis_idx = 0; axis_idx < this->size(); axis_idx++) {
    lim_left = (*this)[axis_idx][0];
    lim_right = (*this)[axis_idx][1];
    dom_target[axis_idx][0] = p[axis_idx] - contract_factor*(p[axis_idx] - lim_left);
    dom_target[axis_idx][1] = p[axis_idx] + contract_factor*(lim_right - p[axis_idx]);
  }
}

// TODO: merge with Point's <<
std::ostream& operator<<(std::ostream& s, const Domain& d) {
  s << "[";
  if (d.size() > 0) {
    for (size_t i = 0; i < d.size() - 1; i++) {
      s << d[i] << ", ";
    }
    s << d[d.size()-1];
  }
  s << "]";
  return s;
}
