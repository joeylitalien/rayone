// core/pathtracer.h
#ifndef PT_CORE_PATHTRACER_H
#define PT_CORE_PATHTRACER_H

// Global include files
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "geometry.h"
#include "shape.h"
#include "renderer.h"
#include "montecarlo.h"

// Global constants
#define RR_DEPTH 5     // Number of bounce before Russian Roulette
#define MAX_DEPTH 10   // Maximum number a ray can bounce
#define EPS 1e-4       // Small nonzero value for ray intersection

// Global forward declarations
class Vec;
class Ray;
class Shape;
struct Intersection;
class Renderer;

// Restrict x value to [0,1] interval
inline double Clamp(double x) {
  return x < 0 ? 0 : x > 1 ? 1 : x;
}

// Gamma correction (y = 2.2) and RGB conversion
inline int ToDisplayValue(double x) {
  return int(pow(Clamp(x), 1./2.2) * 255 + .5);
}

// Thread-safe uniformly distributed pseudo-random number
// See http://linux.die.net/man/3/erand48 for more info
inline double RandomGen(unsigned short *seed) {
  return erand48(seed);
}

// Antialiasing tent filter (approximate sinc filter)
inline void TentFilter(double &dx, double &dy, unsigned short *Xi) {
  double a = 2 * RandomGen(Xi); dx = a < 1 ? sqrt(a) - 1 : 1 - sqrt(2 - a);
  double b = 2 * RandomGen(Xi); dy = b < 1 ? sqrt(b) - 1 : 1 - sqrt(2 - b);
}

// Construct orthonormal frame from vector w
inline void BuildOrthonormalFrame(Vec &u, Vec &v, Vec &w) {
  u = (fabs(w.x) > .1 ? Vec(0,1,0) : Vec(1,0,0)).Cross(w).Norm();
  v = w.Cross(u);
}

// Write image as PPM Portable Bitmap Format
// See http://netpbm.sourceforge.net/doc/ppm.html for more info
inline void SaveImage(char const *fileName, Vec *pixCol, int w, int h) {
  FILE *f = fopen(fileName, "w");
  fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
  for (int p = 0; p < w * h; p++) {
    fprintf(f, "%d %d %d ", ToDisplayValue(pixCol[p].x),
                            ToDisplayValue(pixCol[p].y),
                            ToDisplayValue(pixCol[p].z));
  }
  fclose(f);
}

#endif   // PT_CORE_PATHTRACER_H
