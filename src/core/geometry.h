// core/geometry.h
#ifndef PT_CORE_GEOMETRY_H
#define PT_CORE_GEOMETRY_H

#include "pathtracer.h"

// Vec class declaration
// Vector u = (x, y, z)
class Vec {
public:
  double x, y, z;
  // Constructor
  Vec(double x_= 0, double y_= 0, double z_= 0) { x = x_; y = y_; z = z_; }

  // Operator overloading: Add, flip sign, subtract and mulitply by scalar
  Vec operator+(const Vec &v) const { return Vec(x + v.x, y + v.y, z + v.z); }
  Vec operator-() const { return Vec(-x, -y, -z); }
  Vec operator-(const Vec &v) const { return Vec(x - v.x, y - v.y, z - v.z); }
  Vec operator*(double k) const { return Vec(x * k, y * k, z * k); }

  // Vector operations: dot, cross, point-wise multiplication
  inline double Dot(const Vec &v) const { return x * v.x + y * v.y + z * v.z; }
  // Vec cross(const Vec &v) const {
  //   return Vec(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  // }
  // Test
  Vec operator%(Vec &v) {
    return Vec(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  }
  Vec Mult(const Vec &v) const { return Vec(x * v.x, y * v.y, z * v.z); }

  // Euclidean norm and norm squared
  Vec &Norm() { return *this = *this * (1 / sqrt(x * x + y * y + z * z)); }
};

// Ray class declaration
// Origin o and direction d: r(t) = o + td
class Ray {
public:
  Ray(Vec o_, Vec d_) : o(o_), d(d_) {}
  Vec operator()(double t) const { return o + d * t; }
  Vec o, d;
};

#endif   // PT_CORE_GEOMETRY_H
