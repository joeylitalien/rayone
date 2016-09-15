// core/renderer.h
#ifndef PT_CORE_RENDERER_H
#define PT_CORE_RENDERER_H

#include "pathtracer.h"
#include <vector>

// Forward declaration (shouldn't have to do this)
class Shape;
struct Intersection;

// Render class declaration
// Provide shading and intersecting methods for the scene
class Renderer {
public:
  Renderer(std::vector<Shape *> s) : scene(s) {}
  ~Renderer() {}
  Vec Radiance(const Ray &r, int depth, unsigned short *Xi, int E = 1) const;
  Intersection Intersect(const Ray &r) const;

  std::vector<Shape *> scene;
};

#endif   // PT_CORE_RENDERER_H
