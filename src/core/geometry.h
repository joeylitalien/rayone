#ifndef RT_CORE_GEOMETRY_H
#define RT_CORE_GEOMETRY_H

#include "raytracer.h"
#include "../glm/glm.hpp"

using glm::vec3;

/**
 *   Ray structure
 *   Implement a basic ray with origin o and direction d
 */
struct Ray {
  vec3 o, d;
  Ray(vec3 o_, vec3 d_) : o(o_), d(d_) {}
};

#endif
