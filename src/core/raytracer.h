// core/raytracer.h
#ifndef RT_CORE_RAYTRACER_H
#define RT_CORE_RAYTRACER_H

// Global include files
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "geometry.h"
#include "shape.h"

// Global forward declarations
// Classes
class Vec;
class Ray;
class Shape;

// Functions
Vec shade(const Ray &r);
inline bool intersect(const Ray &r, double &t, int &id);

// Restrict x value to [0,1] interval
inline double clamp(double x) {
  return x < 0 ? 0 : x > 1 ? 1 : x;
}

// Gamma correction (y = 2.2) and RGB conversion
inline int toDisplayValue(double x) {
  return int(pow(clamp(x), 1.0/2.2) * 255 + .5);
}

#endif   // RT_CORE_RAYTRACER_H
