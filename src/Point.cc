#include "Point.h"

#include <cstdlib>	// size_t
#include <cmath>	// std::abs, std::sqrt
#include <exception>	// invalid_argument for operator+
#include <sstream>

Point::Point(std::initializer_list<double> p) : std::vector<double>(p) {}
Point::Point(const Point& p) : std::vector<double>(p) {}
Point::Point() : std::vector<double>() {}
Point::Point(int size) : std::vector<double>(size) {}

bool Point::IsZero(double eps) const {
  for (size_t i = 0; i < size(); i++) {
    if (std::abs((*this)[i]) > eps) {
      return false;
    }
  }
  return true;
}

double Point::L2Norm() const {
  // FIXME: get rid of the loop
  double norm = 0;
  for (size_t i = 0; i < size(); i++) {
    norm += pow((*this)[i], 2);
  }
  return std::sqrt(norm);
}

Point operator* (const Point& p, double r) {
  // FIXME: get rid of the loop
  Point q(p);
  for (size_t i = 0; i < p.size(); i++) {
    q[i] *= r;
  }
  return q;
}

Point operator* (double r, const Point& p) {
  return p * r;
}

Point operator- (const Point& p) {
  return p * (-1);
}

Point operator+ (const Point& p, const Point& q) {
  Point r(p.size());
  if (p.size() != q.size()) {
    std::stringstream ss;
    ss << "Dimension mismatch: " << p.size() << " != " << q.size() << ".";
    throw std::invalid_argument(ss.str());
  }
  for (size_t i = 0; i < r.size(); i++) {
    r[i] = p[i] + q[i];
  }
  return r;
}

Point operator- (const Point& p, const Point& q) {
  return p + q * (-1);
}

Point operator/ (const Point& p, const Point& q) {
  // FIXME: code duplication from +
  Point r(p.size());
  if (p.size() != q.size()) {
    std::stringstream ss;
    ss << "Dimension mismatch: " << p.size() << " != " << q.size() << ".";
    throw std::invalid_argument(ss.str());
  }
  for (size_t i = 0; i < r.size(); i++) {
    r[i] = p[i] / q[i];
  }
  return r;
}

double operator* (const Point& p, const Point& q) {
  // FIXME: get rid of the loop
  double s = 0;
  for (size_t i = 0; i < p.size(); i++) {
    s += p[i] * q[i];
  }
  return s;
}

std::ostream& operator<<(std::ostream& s, const Point& p) {
  s << "[";
  if (p.size() > 0) {
    for (size_t i = 0; i < p.size() - 1; i++) {
      s << p[i] << ", ";
    }
    s << p[p.size()-1];
  }
  s << "]";
  return s;
}
