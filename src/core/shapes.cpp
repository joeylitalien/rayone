#include "shapes.h"

// Compute geometric intersection of sphere with casted ray
// Return t value of ray interesection with sphere (r = o + td)
float Sphere::Intersect(const Ray &ray) const {
  vec3 op = p - ray.o;   // Vector from ray origin to sphere center
  float t, eps = 1e-4;   // Small, nonzero value to handle rounding errors
  float b = dot(op, ray.d);   // Project op onto d
  float det = b * b - dot(op, op) + r * r;   // Pythagorean theorem

  if (det < 0) return 0;   // Two complex roots, no interesections
  else det = sqrt(det);   // Two real roots, take square root

  // Return closest intersection
  return (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
}
