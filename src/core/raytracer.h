#ifndef CORE_RAYTRACER_H
#define CORE_RAYTRACER_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "geometry.h"
#include "shapes.h"
#include "../glm/glm.hpp"

using glm::vec3;

struct Sphere;
struct Ray;

vec3 shade(const Ray &r);
inline bool intersect(const Ray &r, float &t, int &id);

// Restrict x value to [0,1] interval
inline double clamp(double x) {
  return x < 0 ? 0 : x > 1 ? 1 : x;
}

// Gamma correction and conversion to RGB value
inline int toDisplayValue(double x) {
  return int(pow(clamp(x), 1.0/2.2) * 255 + .5);
}

#endif
