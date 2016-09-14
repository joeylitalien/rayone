// core/montecarlo.cpp
#include "montecarlo.h"


// Cosine-weighted hemispherical importance sampling
Vec UniformSampleHemisphere(double xi[2]) {
  double r = sqrt(1 - xi[0] * xi[0]);
  double phi = 2 * M_PI * xi[1];
  return Vec(r * cos(phi), r * sin(phi), xi[0]);
}


// Spherical light importance sampling (solid angle)
Vec UniformSampleCone(double xi[2], double &cosThetaMax) {
  double cosTheta = 1 - xi[0] + xi[0] * cosThetaMax;
  double sinTheta = sqrt(1 - cosTheta * cosTheta);
  double phi = 2 * M_PI * xi[1];
  return Vec(cos(phi) * sinTheta, sin(phi) * sinTheta, cosTheta);
}


// Phong cosine-power hemispherical importance sampling
// Follow RRT, ???
Vec PhongCosPowerHemispherical(unsigned short int *Xi) {

}
