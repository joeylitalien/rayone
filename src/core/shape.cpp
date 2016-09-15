// core/shape.cpp
#include "shape.h"


// Virtual methods
double Shape::Intersect(const Ray &ray) const {
  printf("Unimplemented Shape::Intersect() method called\n");
  return 0;
}

Vec Shape::SurfaceNormal(const Ray &r, double t) const {
  printf("Unimplemented Shape:SurfaceNormal() method called\n");
  return Vec();
}

// Compute geometric intersection of sphere with casted ray
// Return t value of ray interesection with sphere (r = o + td)
// See en.wikipedia.org/wiki/Line-sphere_intersection for derivation
double Sphere::Intersect(const Ray &r) const {
  Vec op = pos - r.o;
  double t;
  double b = op.Dot(r.dir);
  double dsc = b * b - op.Dot(op) + rad * rad;
  if (dsc < 0) return 0; else dsc = sqrt(dsc);
  return (t = b - dsc) > EPS ? t : ((t = b + dsc) > EPS ? t : 0);
}

Vec Sphere::SurfaceNormal(const Ray &r, double t) const {
  Vec n = (r(t) - pos).Norm();
  return n.Dot(r.dir) < 0 ? n : -n;
}

// Cube::Cube(const double &l_, const Vec &p_, const Vec &e_, const Vec &c_,
//            const Mat_t &m_) : l(l_), Shape(p_, e_, c_, m_) {
//   lo = p - Vec(1,1,1) * (l/2);
//   hi = p + Vec(1,1,1) * (l/2);
// }
//
// double Cube::Intersect(const Ray &ray) const {
//   printf("Unimplemented Cube::Intersect() method called\n");
//   return 0;
// }
