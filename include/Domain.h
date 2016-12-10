#ifndef DOMAIN_H_
#define DOMAIN_H_

#include <vector>
#include <ostream>

#include "Point.h"

/**
 * A rectangular domain in \f$\mathbf{R}^k\f$.
 */
class Domain : public std::vector<Point> {
public:
  /**
   * Specify a domain by a list of Point's, each of which sets a minimum and a
   * maximum value for the corresponding axis.
   *
   * Thus {{1, 2}, {3, 4}, {5, 6}} describes a domain in \f$\mathbf{R}^3\f$ with
   * obvious boundaries.
   */
	Domain(std::initializer_list<Point> d) : std::vector<Point>(d) {};
	// Domain(Domain&& d) : std::vector<Point>(d) {};
	// Domain(const Domain& d) : std::vector<Point>(d) {};
  /**
   * Check whether a point belongs to the domain (including its border).
   * @param p target point.
   * @return True if point belongs to the domain, false otherwise.
   */
	bool Contains(const Point& p);
	// FIXME: const &
  /**
   * Center the current domain around the point, contracting its side by the
   * specified factor.
   * @param dom_target domain to be contracted.
   * @param p point to become the center of the new domain.
   * @param contract_factor contraction factor by which each axis of the domain gets
   * multiplied.
   */
	void ZoomToPoint(Domain& dom_target, const Point& p, double contract_factor);
};

std::ostream& operator<<(std::ostream& s, const Domain& d);

#endif	// DOMAIN_H_
