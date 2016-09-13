// core/geometry.h
#ifndef RT_CORE_GEOMETRY_H
#define RT_CORE_GEOMETRY_H

#include "raytracer.h"

// Vec class declaration
// Vector u = (x, y, z)
class Vec {
public:
  Vec() { x = y = z = 0.; }
  Vec(const double &w) { x = y = z = w; }
  Vec(const double &x_, const double &y_, const double &z_)
    : x(x_), y(y_), z(z_) {}

  // Operator overloading: Add, subtract and mulitply by scalar
  Vec operator+(const Vec &v) const { return Vec(x + v.x, y + v.y, z + v.z); }
  Vec operator-(const Vec &v) const { return Vec(x - v.x, y - v.y, z - v.z); }
  Vec operator*(double s) const { return Vec(x * s, y * s, z * s); }

  // Vector operations: dot, cross, point-wise multiplication and norm
  double dot(const Vec &v) const { return x * v.x + y * v.y + z * v.z; }
  Vec cross(const Vec &v) const {
    return Vec(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  }
  Vec mult(const Vec &v) const { return Vec(x * v.x, y * v.y, z * v.z); }
  Vec &norm() { return *this = *this * (1.0 / sqrt(x * x + y * y + z * z)); }

  double x, y, z;
};

// Ray class declaration
// Origin o and direction d: r(t) = o + td
class Ray {
public:
  Ray(Vec o_, Vec d_) : o(o_), d(d_) {}
  Vec o, d;
};

#endif   // RT_CORE_GEOMETRY_H
