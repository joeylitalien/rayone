// core/primitive.h
#ifndef RT_CORE_PRIMITIVE_H
#define RT_CORE_PRIMITIVE_H

#include "raytracer.h"
#include "geometry.h"
#include "diffgeom.h"
#include "../glm/glm.hpp"

using glm::vec3;
struct Ray;

/**
 *   General shape
 *   Position p, Emission e, Color c
 */
class Primitive {
public:
  // Primitive public methods
  virtual ~Primitive() {}
  Primitive(vec3 p_, vec3 e_, vec3 c_) : p(p_), e(e_), c(c_) {}

  // Primitive public data
  vec3 p, e, c;
};


/**
 *   Sphere of radius r
 */
class Sphere : public Primitive {
public:
  // Sphere public methods
  Sphere(float r_, vec3 p_, vec3 e_, vec3 c_) : r(r_), Primitive(p_, e_, c_) {}
  float Intersect(const Ray &ray) const;

  // Sphere public data
  float r;
};

#endif   // RT_CORE_PRIMITIVE_H
