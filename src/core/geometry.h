// core/geometry.h
#ifndef RT_CORE_GEOMETRY_H
#define RT_CORE_GEOMETRY_H

#include "raytracer.h"
#include "../glm/glm.hpp"
using glm::vec3;

/**
 *   Ray class
 *   Origin o and Direction d: r(t) = o + td
 */
class Ray {
public:
  // Ray public methods
  Ray(vec3 o_, vec3 d_) : o(o_), d(d_) {}
  vec3 operator()(float t) const { return o + d * t; }

  // Ray public data
  vec3 o, d;
};

#endif   // RT_CORE_GEOMETRY_H
