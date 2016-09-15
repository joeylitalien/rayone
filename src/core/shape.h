// core/shape.h
#ifndef PT_CORE_SHAPE_H
#define PT_CORE_SHAPE_H

#include "pathtracer.h"
#include "geometry.h"

// New material type declaration
// DIFFuse (most objects), SPECular (e.g. mirror) or REFRactive (e.g. glass)
enum mat_t { DIFF, SPEC, REFR };
enum shape_t { SH, SPHR, TRGL };

// Shape class declaration
// Position pos, emission emi & color col
// Material mat (diffuse, specular & refractive)
class Shape {
public:
  Shape(const Vec &p_, const Vec &e_, const Vec &c_, const mat_t &m_,
    const shape_t &s_) : pos(p_), emi(e_), col(c_), mat(m_), shp(s_) {}
  virtual ~Shape() {}
  virtual double Intersect(const Ray &r) const;
  virtual Vec SurfaceNormal(const Ray &r, double t) const;

  Vec pos, emi, col;
  mat_t mat;
  shape_t shp;
};

// Sphere subclass declaration
// Sphere of radius rad
class Sphere : public Shape {
public:
  Sphere(const double &r_, const Vec &p_, const Vec &e_, const Vec &c_,
    const mat_t &m_) : Shape(p_, e_, c_, m_, SPHR), rad(r_) {}
  double Intersect(const Ray &ray) const;
  Vec SurfaceNormal(const Ray &ray, double t) const;

  double rad;
};

// Intersection struct declaration
// Ray-object intersection (object, t parameter along a ray) pair
struct Intersection {
  Intersection(Shape *o_, const double t_) : obj(o_), t(t_) {}
  ~Intersection() {}

  Shape *obj;
  double t;
};

// Cube subclass declaration
// Cube of length l
// class Cube : public Shape {
// public:
//   Cube(const double &l_, const Vec &p_, const Vec &e_, const Vec &c_,
//        const Mat_t &m_) : l(l_), Shape(p_, e_, c_, m_) {
//     lo = p - Vec(1,1,1) * (l/2);
//     hi = p + Vec(1,1,1) * (l/2);
//   }
//   double Intersect(const Ray &ray) const;
//
//   double l;
//   Vec lo, hi;
// };

#endif   // PT_CORE_SHAPE_H
