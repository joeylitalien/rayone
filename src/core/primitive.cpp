// core/primitive.cpp
#include "primitive.h"

/**
 *   Compute geometric intersection of sphere with casted ray
 *   Return t value of ray interesection with sphere (r = o + td)
 *   ---
 *   Take vector op between ray origin and sphere center, project onto ray
 *   direction vector d and apply Pythagorean theorem to find interesection
 *   See en.wikipedia.org/wiki/Line-sphere_intersection for derivation
 */
float Sphere::Intersect(const Ray &ray) const {
  vec3 op = p - ray.o;
  float t, eps = 1e-4;   // Small nonzero value to handle rounding errors
  float b = dot(op, ray.d);
  float det = b * b - dot(op, op) + r * r;

  if (det < 0) return 0;   // Check for real determinant
  else det = sqrt(det);

  // Return closest intersection
  return (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
}
