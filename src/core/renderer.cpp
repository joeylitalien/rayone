// core/renderer.cpp
#include "renderer.h"

// Main shader
Vec Renderer::Radiance(const Ray &r, int depth, unsigned short *Xi, int E)
      const {
  if (depth > MAX_DEPTH) return Vec();     // Check for ray termination

  Intersection h = Intersect(r);
  Shape *hitObj = h.obj;
  double t = h.t;

  Vec x = r(t);                          // Get intersection point
  Vec n = hitObj->SurfaceNormal(r, t);   // Properly oriented surface normal
  Vec c = hitObj->col;                   // Surface color

  // Russian Roulette (RR) rejection sampling
  // Use max component of RGB surface color, activate when RR_DEPTH is reached
  double p = c.Max();
  if (++depth > RR_DEPTH || !p) {
    if (RandomGen(Xi) < p) c = c * (1./p);
    else return hitObj->emi * E;
  }

  // Ideal diffuse reflection
  if (hitObj->mat == DIFF) {
    // Cosine-weighted hemispherical importance sampling
    double xi[2] = { RandomGen(Xi), RandomGen(Xi) };
    Vec u, v;
    BuildOrthonormalFrame(u, v, n);
    Vec d = UniformSampleHemisphere(xi);
    d = (u * d.x + v * d.y + n * d.z).Norm();

    // Loop over all objects in the scene
    Vec e;
    for (Shape *s : scene) {
      if (s->emi.Max() == 0) continue;   // Non-emissive object

      // Spherical light importance sampling
      Vec us, vs, ns = s->pos - x;
      BuildOrthonormalFrame(us, vs, ns);
      double srad = 1.5;   // Ugly fix until nonspherical lights get implemented
      double cosThetaMax = sqrt(1 - srad * srad / (-ns).Dot(-ns));
      double xi[2] = { RandomGen(Xi), RandomGen(Xi) };
      Vec l = UniformSampleCone(xi, cosThetaMax);
      l = (us * l.x + vs * l.y + ns * l.z).Norm();

      // Shadow ray to check for occlusion
      if (Intersect(Ray(x, l)).obj == s) {
        double omg = 1. / UniformConePDF(cosThetaMax);
        e = e + c.Mult(s->emi * l.Dot(n) * omg) * M_1_PI;
      }
    }

    // Recursive call with random ray direction
    // Turn off emissive term at the next recursive level with E = 0
    return e + hitObj->emi * E + c.Mult(Radiance(Ray(x, d), depth, Xi, 0));
  }

  // Ideal specular reflection
  else if (hitObj->mat == SPEC) {
    return hitObj->emi + c.Mult(Radiance(Ray(x, r.dir - n * 2 * n.Dot(r.dir)),
                             depth, Xi));
  }

  // Handle other material later, return object emission for now
  else {
    return hitObj->emi;
  }
}

// Intersect ray with scene
Intersection Renderer::Intersect(const Ray &r) const {
  Shape *obj = NULL;
  double d, t = 1e20f;
  for (Shape *s : scene) {
    if ((d = s->Intersect(r)) && d < t) {
      obj = s;
      t = d;
    }
  }
  return Intersection(obj, t);
}
