#ifndef POINT_H_
#define POINT_H_

#include <vector>
#include <ostream>

/**
 * A point ("vector") in \f$\mathbf{R}^k\f$.
 */
class Point : public std::vector<double> {
  public:
    Point(std::initializer_list<double> p) : std::vector<double>(p) {};
    // Point(Point&& p) : std::vector<double>(p) {};
    Point(const Point& p) : std::vector<double>(p) {};
    Point() : std::vector<double>() {};
    Point(int size) : std::vector<double>(size) {};
    bool IsZero(double eps=10e-6);
    double L2Norm() const;
};

/**
 * Scalar (coordinate-wise) vector multiplication.
 * @param A point.
 * @param A scalar.
 * @return Magnified / contracted vector.
 */
Point operator* (const Point& p, double r);
Point operator* (double r, const Point& p);
Point operator- (const Point& p);
Point operator+ (const Point& p, const Point& q);
Point operator- (const Point& p, const Point& q);
Point operator/ (const Point& p, const Point& q);
double operator* (const Point& p, const Point& q);
std::ostream& operator<<(std::ostream& s, const Point& p);

#endif	// POINT_H_
