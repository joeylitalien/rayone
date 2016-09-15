// core/montecarlo.cpp
#include "montecarlo.h"

// Cosine-weighted hemispherical importance sampling
Vec UniformSampleHemisphere(double xi[2]) {
  double r = sqrt(1 - xi[0] * xi[0]);
  double phi = 2. * M_PI * xi[1];
  return Vec(r * cos(phi), r * sin(phi), xi[0]);
}

// Spherical light importance sampling (solid angle)
Vec UniformSampleCone(double xi[2], double cosThetaMax) {
  double cosTheta = 1 - xi[0] + xi[0] * cosThetaMax;
  double sinTheta = sqrt(1 - cosTheta * cosTheta);
  double phi = 2. * M_PI * xi[1];
  return Vec(cos(phi) * sinTheta, sin(phi) * sinTheta, cosTheta);
}

// Probability of choosing any given direction within cone
double UniformConePDF(double cosThetaMax) {
  return 1. / (2. * M_PI * (1 - cosThetaMax));
}

// Phong cosine-power hemispherical importance sampling
// s is the surface shininess
Vec PhongSampleHemisphere(double xi[2], double s) {
  double phi = 2. * M_PI * xi[0];
  double theta = acos(pow(1. - xi[1], 1./ (s + 1)));
  double x = sin(theta) * cos(phi);
  double y = sin(theta) * sin(theta);
  double z = cos(theta);
  return Vec(x, y, z);
}
