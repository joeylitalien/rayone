/**
 *   @file     raytracer.cpp
 *   @author   Joey Litalien
 *   @version  1.1
 *
 *   A minimalistic ray tracer for the course ECSE 689 Physically Based
 *   Rendering Fall 2016 at McGill University.
 */

#include "../core/raytracer.h"

// Construct simple scene with 3 spheres and 5 walls
Sphere spheres[] = {
  // Walls (left, right, back, floor, ceiling)
  Sphere(1e5,  Vec(1e5 + 1, 40.8, 81.6),   Vec(), Vec(.75, .25, .25), DIFF),
  Sphere(1e5,  Vec(-1e5 + 99, 40.8, 81.6), Vec(), Vec(.25, .25, .75), DIFF),
  Sphere(1e5,  Vec(50, 40.8, 1e5),         Vec(), Vec(.75),           DIFF),
  Sphere(1e5,  Vec(50, 1e5, 81.6),         Vec(), Vec(.75),           DIFF),
  Sphere(1e5,  Vec(50, -1e5 + 81.6, 81.6), Vec(), Vec(.75),           DIFF),
  // Sphere objects
  Sphere(16.5, Vec(27, 16.5, 47),          Vec(), Vec(.999),          DIFF),
  Sphere(16.5, Vec(73, 16.5, 78),          Vec(), Vec(.999),          DIFF),
  Sphere(10.5, Vec(50, 68.6 - .27, 81.6),  Vec(400.), Vec(1.),        DIFF)
};

int numSpheres = sizeof(spheres) / sizeof(Sphere);

// Pixel shader
// Test for intersection and return shading value
Vec shade(const Ray &r) {
  double t;
  int id = 0;
  if (!intersect(r, t, id)) return Vec();

  const Sphere &obj = spheres[id];
  Vec x = r.o + r.d * t;   // Intersection point
  Vec n = (x - obj.p).norm();   // Normal

  // if (obj.mat == DIFF) {
  //   double rdAng = 2 * M_PI * erand48(Xi);
  //   double rdDist = sqrt(erand48(Xi));
  // }

  return obj.c + n;   // Return shading value (normal & color mix)
}

// Intersect ray with scene
// Take a ray, a parameter t and an object ID, output if interesection (bool)
inline bool intersect(const Ray &r, double &t, int &id) {
  double d, inf = t = 1e20;
  for (int i = numSpheres; i--;) {   // Check interesection against all spheres
    if ((d = spheres[i].Intersect(r)) && d < t) {   // Intersection found
      t = d;   // Update t parameter
      id = i;   // Store sphere ID
    }
  }
  return t < inf;
}

// Main render loop
// Render image seen from a camera and write image to PPM file
int main(int argc, char *argv[]) {
  int w = 800, h = 600;   // Set display resolution

  // tan(30 / 180 * pi) == 0.57735 serves as camera field of view
  Ray camera(Vec(50, 50, 275.0), Vec(0, -0.05, -1).norm());   // Camera
  Vec cx = Vec(w * 0.57735 / h, 0., 0.);   // Camera x vector
  Vec cy = cx.cross(camera.d).norm() * 0.57735;   // Camera up vector

  Vec pixelValue, *pixelColors = new Vec[w * h];   // New pixel grid

  // Tell compiler to use OMP loop scheduler for parallel computing
  #pragma omp parallel for schedule(dynamic, 1) private(pixelValue)

  // Assign value to each pixel in grid
  for (int y = 0; y < h; y++) {
    fprintf(stderr, "\r%5.2f%%", 100.*y / (h - 1));
    for (int x = 0; x < w; x++) {
      int idx = (h - y - 1) * w + x;
      pixelValue = Vec();
      Vec cameraRayDir = cx * (double(x) / w - .5f) +
                          cy * (double(y) / h - .5f) +
                          camera.d;
      // Shade point
      pixelValue = shade(Ray(camera.o, cameraRayDir.norm()));
      // Convert shaded point to RGB value for display
      pixelColors[idx] = Vec(clamp(pixelValue.x),
                             clamp(pixelValue.y),
                             clamp(pixelValue.z));
    }
  }

  fprintf(stderr,"\n");

  // Write image as PPM Portable Bitmap Format
  // See http://netpbm.sourceforge.net/doc/ppm.html for more info
  FILE *f = fopen("image.ppm", "w");
  fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
  for (int p = 0; p < w * h; p++) {
    fprintf(f,"%d %d %d ", toDisplayValue(pixelColors[p].x),
                           toDisplayValue(pixelColors[p].y),
                           toDisplayValue(pixelColors[p].z));
  }
  fclose(f);   // Close file
  delete[] pixelColors;   // Free memory
  return 0;
}
