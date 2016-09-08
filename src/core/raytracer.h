// core/raytracer.h
#ifndef CORE_RAYTRACER_H
#define CORE_RAYTRACER_H

// Global include files
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "geometry.h"
#include "primitive.h"
#include "light.h"
#include "../glm/glm.hpp"
using glm::vec3;

// Global forward declarations
class Sphere;
class Ray;
class Light;

vec3 shade(const Ray &r);
inline bool intersect(const Ray &r, float &t, int &id);

// Restrict x value to [0,1] interval
inline float clamp(float x) {
  return x < 0 ? 0 : x > 1 ? 1 : x;
}

// Gamma correction and conversion to RGB value
inline int toDisplayValue(double x) {
  return int(pow(clamp(x), 1.0/2.2) * 255 + .5);
}

// Linear interpolation between u and v
inline double lerp(float t, float u, float v) {
	return (1.0 - t) * u + t * v;
}

#endif   // CORE_RAYTRACER_H
