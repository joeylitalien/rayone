// core/sampler.h
#ifndef PT_CORE_MONTECARLO_H
#define PT_CORE_MONTECARLO_H

#include "pathtracer.h"


// Monte Carlo sampling methods
Vec UniformSampleHemisphere(double xi[2]);
Vec UniformSampleCone(double xi[2], double cosThetaMax);
Vec PhongSampleHemisphere(double xi[2], double s);
double UniformConePDF(double cosThetaMax);

#endif   // PT_CORE_MONTECARLO_H
