#ifndef POINT_H_
#define POINT_H_

#include <vector>
#include <ostream>
#include <string>

/**
 * A point ("vector") in \f$\mathbf{R}^k\f$.
 */
class Point : public std::vector<double> {
  public:
    Point(std::initializer_list<double> p);
    // Point(Point&& p) : std::vector<double>(p) {};
    Point(const Point& p);
    Point();
    Point(int size);
    std::string ToString() const;
    bool IsZero(double eps=10e-6) const;
    double L2Norm() const;
};

/**
 * Scalar (coordinate-wise) vector multiplication.
 * @param p point
 * @param r scalar
 * @return Magnified / contracted vector
 */
Point operator* (const Point& p, double r);
Point operator* (double r, const Point& p);
Point operator- (const Point& p);
Point operator+ (const Point& p, const Point& q);
Point operator- (const Point& p, const Point& q);
/**
 * @brief Coordinate-wise division of two points
 * @param p
 * @param q
 * @return point p/q
 */
Point operator/ (const Point& p, const Point& q);
/**
 * @brief Dot-product of two points.
 * @param p
 * @param q
 * @return point p*q
 */
double operator* (const Point& p, const Point& q);
std::ostream& operator<<(std::ostream& s, const Point& p);

#endif	// POINT_H_
