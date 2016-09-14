// core/sampler.h
#ifndef PT_CORE_MONTECARLO_H
#define PT_CORE_MONTECARLO_H

#include "pathtracer.h"

// Monte Carlo sampling methods
Vec UniformSampleHemisphere(double xi[2]);
Vec UniformSampleCone(double xi[2], double &cosThetaMax);
Vec PhongCosPowerHemispherical(unsigned short int *Xi);

#endif   // PT_CORE_MONTECARLO_H
