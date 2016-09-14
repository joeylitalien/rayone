// core/pathtracer.h
#ifndef PT_CORE_PATHTRACER_H
#define PT_CORE_PATHTRACER_H

// Global include files
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "geometry.h"
#include "shape.h"
#include "renderer.h"

// Global constants
#define RR_DEPTH 5
#define MAX_DEPTH 10

// Global forward declarations
class Vec;
class Ray;
class Shape;
class Renderer;

// Restrict x value to [0,1] interval
inline double Clamp(double x) {
  return x < 0 ? 0 : x > 1 ? 1 : x;
}

// Gamma correction (y = 2.2) and RGB conversion
inline int ToDisplayValue(double x) {
  return int(pow(Clamp(x), 1./2.2) * 255 + .5);
}

// Antialiasing tent filter
// See http://computergraphics.stackexchange.com/q/3868 for more info
inline void TentFilter(double &dx, double &dy, unsigned short int *Xi) {
  double a = 2 * erand48(Xi); dx = a < 1 ? sqrt(a) - 1 : 1 - sqrt(2 - a);
  double b = 2 * erand48(Xi); dy = b < 1 ? sqrt(b) - 1 : 1 - sqrt(2 - b);
}

#endif   // PT_CORE_PATHTRACER_H
