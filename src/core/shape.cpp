// core/shape.cpp
#include "shape.h"

// Not implemented
double Shape::Intersect(const Ray &ray) const {
  return 0;
}

// Compute geometric intersection of sphere with casted ray
// Return t value of ray interesection with sphere (r = o + td)
// ---
// Take vector op between ray origin and sphere center, project onto ray
// direction vector d and apply Pythagorean theorem to find interesection
// See en.wikipedia.org/wiki/Line-sphere_intersection for derivation
double Sphere::Intersect(const Ray &ray) const {
  Vec op = p - ray.o;
  double t, eps = 1e-4;   // Small nonzero value to handle rounding errors
  double b = op.dot(ray.d);
  double det = b * b - op.dot(op) + r * r;
  if (det < 0) return 0; else det = sqrt(det);
  return (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
}

// Not implemented
double Cube::Intersect(const Ray &ray) const {
  return 0;
}
