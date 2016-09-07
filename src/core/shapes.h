#ifndef RT_CORE_SHAPES_H
#define RT_CORE_SHAPES_H

#include "raytracer.h"
#include "geometry.h"
#include "../glm/glm.hpp"

using glm::vec3;
struct Ray;

/**
 *   Sphere primitive
 *   Radius r, position p, emission e and color c
 */
struct Sphere {
  float r;   // Sphere radius
  vec3 p, e, c;   // p = position, e = emission/intensity, c = color

  // Default constructor
  Sphere(float r_, vec3 p_, vec3 e_, vec3 c_) : r(r_), p(p_), e(e_), c(c_) {}

  // Intersection method
  float Intersect(const Ray &ray) const;
};

#endif
