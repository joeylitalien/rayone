// core/renderer.cpp
#include "shape.h"

// Main shader
Vec Renderer::Radiance(const Sphere (&scene)[sceneSize], const Ray &r,
                       int depth, unsigned short *Xi, int E) {
  double t;
  int id = 0;
  if (!Intersect(scene, r, t, id)) return Vec();
  const Sphere &obj = scene[id];

  // Ray termination
  if (depth > MAX_DEPTH) return Vec();

  Vec x = r.o + r.d * t;             // Get intersection point
  Vec n = (x - obj.p).Norm();        // Surface normal
  Vec nl = n.Dot(r.d) < 0 ? n : -n;   // Orient surface normal
  Vec f = obj.c;                     // Surface color

  // Russian Roulette (RR) for reflectivity
  // Stop recursion based on surface reflectivity
  // Use max component of RGB surface color, activate when RR_DEPTH is reached
  double p = fmax(fmax(f.x, f.y), fmax(f.x, f.z));
  if (++depth > RR_DEPTH || !p) {
    if (erand48(Xi) < p) f = f * (1./p);
    else return obj.e * E;   // RR
  }

  // // Ideal diffuse reflection
  // if (obj.m == DIFF) {
    // Get random angle and distance from normal distribution
    double phi = 2 * M_PI * erand48(Xi);
    double q = erand48(Xi), q_ = sqrt(q);

    // Build orthonormal uvw-frame
    Vec u, v, w = nl;
    BuildOrthonormalFrame(u, v, w);

    // Random reflection ray
    // Follow Realistic Ray Tracing (RRT) by Shirley & Morley, 10.4.1 (p154)
    Vec d = u * cos(phi) * q_ + v * sin(phi) * q_ + w * sqrt(1 - q);
    d = d.Norm();

    // Loop over all scene objects (direct lighting)
    Vec e;
    for (int i = 0; i < sceneSize; i++) {
      const Sphere &s = scene[i];
      if (s.e.x <= 0 && s.e.y <= 0 && s.e.z <= 0) continue;   // Non-emissive

      // Compute sample direction based on random distribution
      // Follow RRT, 13.2 (p198)
      Vec us, vs, ws = s.p - x;
      BuildOrthonormalFrame(us, vs, ws);
      double cosAmax = sqrt(1 - s.r * s.r / (x - s.p).Dot(x - s.p));
      double xi = erand48(Xi), xi_ = erand48(Xi);
      double cosA = 1 - xi + xi * cosAmax;
      double sinA = sqrt(1 - cosA * cosA);
      double psi = 2 * M_PI * xi_;
      Vec l = us * cos(psi) * sinA + vs * sin(psi) * sinA + ws * cosA;
      l = l.Norm();

      // Shadow ray
      // Check for occlusion with ray and update lighting
      if (Intersect(scene, Ray(x, l), t, id) && id == i) {
        double omg = 2 * M_PI * (1 - cosAmax);
        e = e + f.Mult(s.e * l.Dot(w) * omg) * M_1_PI;
      }
    }

    // Recursive call with random ray direction
    // Turn off emissive term at the next recursive level with E = 0
    return e + obj.e * E + f.Mult(Radiance(scene, Ray(x, d), depth, Xi, 0));
}


// Intersect ray with scene
bool Renderer::Intersect(const Sphere (&scene)[sceneSize], const Ray &r,
                                double &t, int &id) {
  double d, inf = t = 1e20;
  for (int i = sceneSize; i--;) {   // Check interesection against all spheres
    if ((d = scene[i].Intersect(r)) && d < t) {   // Intersection found
      t = d;    // Update t parameter and s
      id = i;   // Store sphere ID
    }
  }
  return t < inf;
}


// Construct orthonormal frame around a vector w
inline void Renderer::BuildOrthonormalFrame(Vec &u, Vec &v, Vec &w) {
  u = ((fabs(w.x) > .1 ? Vec(0, 1) : Vec(1)) % w).Norm();
  v = w % u;
}
