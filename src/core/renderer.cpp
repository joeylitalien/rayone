// core/renderer.cpp
#include "shape.h"
#include "montecarlo.h"
using namespace std;

// Main shader
Vec Renderer::Radiance(const Sphere (&scene)[sceneSize], const Ray &r,
                       int depth, unsigned short *Xi, int E) {
  if (depth > MAX_DEPTH) return Vec();     // Check for ray termination

  double t;
  int id = 0;
  if (!Intersect(scene, r, t, id)) return Vec();   // No intersection
  const Sphere &obj = scene[id];

  Vec x = r(t);                      // Get intersection point
  Vec n = obj.SurfaceNormal(r, t);   // Properly oriented surface normal
  Vec c = obj.c;                     // Surface color

  // Russian Roulette (RR) rejection sampling
  // Use max component of RGB surface color, activate when RR_DEPTH is reached
  double p = c.max();
  if (++depth > RR_DEPTH || !p) {
    if (erand48(Xi) < p) c = c * (1./p);
    else return obj.e * E;   // RR
  }

  // Ideal diffuse reflection
  if (obj.m == DIFF) {
    // Cosine-weighted hemispherical importance sampling
    double xi[2] = { erand48(Xi), erand48(Xi) };
    Vec u, v;
    BuildOrthonormalFrame(u, v, n);
    Vec d = UniformSampleHemisphere(xi);
    d = (u * d.x + v * d.y + n * d.z).Norm();

    // Loop over all objects in the scene
    Vec e;
    for (int i = 0; i < sceneSize; ++i) {
      const Sphere &s = scene[i];
      if (s.e.max() == 0) continue;   // Non-emissive object

      // Spherical light importance sampling
      Vec us, vs, ns = s.p - x;
      BuildOrthonormalFrame(us, vs, ns);
      double cosThetaMax = sqrt(1 - s.r * s.r / (-ns).Dot(-ns));
      double xi[2] = { erand48(Xi), erand48(Xi) };
      Vec l = UniformSampleCone(xi, cosThetaMax);
      l = (us * l.x + vs * l.y + ns * l.z).Norm();

      // Shadow ray
      // Check for occlusion with ray and update lighting
      if (Intersect(scene, Ray(x, l), t, id) && id == i) {
        double omg = 2 * M_PI * (1 - cosThetaMax);
        e = e + c.Mult(s.e * l.Dot(n) * omg) * M_1_PI;
      }
    }

    // Recursive call with random ray direction
    // Turn off emissive term at the next recursive level with E = 0
    return e + obj.e * E + c.Mult(Radiance(scene, Ray(x, d), depth, Xi, 0));
  }

  // Ideal specular reflection --- Follow RRT, Section 12.2.2 (p174)
  else if (obj.m == SPEC) {
    return obj.e + c.Mult(Radiance(scene, Ray(x, r.d - n * 2 * n.Dot(r.d)),
                                   depth, Xi));
  }
}


// Intersect ray with scene
bool Renderer::Intersect(const Sphere (&scene)[sceneSize], const Ray &r,
                                double &t, int &id) {
  double d, inf = t = 1e20;
  for (int i = sceneSize; i--;) {   // Check interesection against all objects
    if ((d = scene[i].Intersect(r)) && d < t) {   // Intersection found
      t = d;    // Update t parameter
      id = i;   // Store sphere ID
    }
  }
  return t < inf;
  // Shape *hitObj = NULL;
  // t = 1e20;
  // for (Shape *obj : scene) {
  //   if ((d = obj->Intersect(r)) && d < t) {
  //     hitObj = obj;
  //     t = d;
  //   }
  // }
}
