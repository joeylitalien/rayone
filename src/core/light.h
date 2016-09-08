// core/light.h
#ifndef RT_CORE_LIGHT_H
#define RT_CORE_LIGHT_H

#include "raytracer.h"
#include "../glm/glm.hpp"
using namespace glm;


/**
 * Point light
 * Position p, Intensity i
 */
class Light {
public:
  // Light public methods
  Light(vec3 p_, float i_) : p(p_), i(i_) {}

  // Light public data
  vec3  p;
  float i;
};

#endif
