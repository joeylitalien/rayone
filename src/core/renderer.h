// core/renderer.h
#ifndef PT_CORE_RENDERER_H
#define PT_CORE_RENDERER_H

#include "pathtracer.h"

// Forward declaration
class Sphere;

// Render class declaration
// Provide shading and intersecting methods for spheres
class Renderer {
protected:
  static const int sceneSize = 9;
public:
  Renderer() {}
  ~Renderer() {}
  Vec Radiance(const Sphere (&scene)[sceneSize], const Ray &r, int depth,
               unsigned short *Xi, int E = 1);
  bool Intersect(const Sphere (&scene)[sceneSize], const Ray &r, double &t,
                 int &id);
  inline void BuildOrthonormalFrame(Vec &u, Vec &v, Vec &w);
};

#endif   // PT_CORE_RENDERER_H
