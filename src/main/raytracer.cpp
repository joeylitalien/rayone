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
// 5 giant spheres as locally flat walls, 3 small spheres as actual spheres
Sphere spheres[] = {
  // Left wall
  Sphere(1e5, vec3(1e5 + 1, 40.8, 81.6), vec3(0, 0, 0), vec3(.75, .25, .25)),
  // Right wall
  Sphere(1e5, vec3(-1e5 + 99, 40.8, 81.6), vec3(0, 0, 0), vec3(.25, .25, .75)),
  // Back wall
  Sphere(1e5, vec3(50, 40.8, 1e5), vec3(0, 0, 0), vec3(.75, .75, .75)),
  // Floor
  Sphere(1e5, vec3(50, 1e5, 81.6), vec3(0, 0, 0), vec3(.75, .75, .75)),
  // Ceiling
  Sphere(1e5, vec3(50, -1e5 + 81.6, 81.6), vec3(0, 0, 0), vec3(.75, .75, .75)),
  // Sphere objects
  Sphere(16.5, vec3(27, 16.5, 47), vec3(0, 0, 0), vec3(.999, .999, .999)),
  Sphere(16.5, vec3(73, 16.5, 78), vec3(0, 0, 0), vec3(.999, .999, .999)),
  Sphere(10.5, vec3(50, 68.6 - .27, 81.6), vec3(400, 400, 400), vec3(1, 1, 1))
};

/**
 *   Pixel shader
 *   Test for intersection and return shading value
 */
vec3 shade(const Ray &r) {
  float t;
  int id = 0;
  if (!intersect(r, t, id))   // No interesections, return empty vector
    return vec3();

  const Sphere &obj = spheres[id];   // Else, get sphere ID
  vec3 x = r.o + r.d * t;   // Retrieve point on sphere
  vec3 n = normalize(x - obj.p);   // Compute normal at this point

  return n + obj.c;   // Return shading value (normal & color mix)
}

/**
 *   Intersect ray with scene
 *   Take a ray, a parameter t and an object ID, output if interesection (bool)
 */
inline bool intersect(const Ray &r, float &t, int &id) {
  double n = sizeof(spheres) / sizeof(Sphere);
  double d, inf = t = 1e20;

  for (int i = int(n); i--;) {   // Check interesection against all spheres
    if ((d = spheres[i].Intersect(r)) && d < t) {   // Intersection found
      t = d;   // Update t parameter
      id = i;   // Store sphere ID
    }
  }

  return t < inf;
}


/**
 *   Main render loop
 *   Render image seen from a camera and write image to PPM file
 */
int main(int argc, char *argv[]) {
  int w = 800, h = 600;   // Set display resolution

  // tan(30 / 180 * pi) == 0.57735 serves as camera field of view
  Ray camera(vec3(50, 50, 275.0), normalize(vec3(0, -0.05, -1)));   // Camera
  vec3 cx = vec3(w * 0.57735 / h, 0., 0.);   // Camera x vector
  vec3 cy = normalize(cross(cx, camera.d)) * 0.57735f;   // Camera up vector

  vec3 pixelValue, *pixelColors = new vec3[w * h];   // New pixel grid

  // Tell compiler to use OMP loop scheduler for parallel computing
  #pragma omp parallel for schedule(dynamic, 1) private(pixelValue)

  // Assign value to each pixel in grid
  for (int y = 0; y < h; y++) {
    fprintf(stderr, "\r%5.2f%%", 100.*y / (h - 1));
    for (int x = 0; x < w; x++) {
      int idx = (h - y - 1) * w + x;
      pixelValue = vec3();
      vec3 cameraRayDir = cx * (float(x) / w - .5f) +
                          cy * (float(y) / h - .5f) +
                          camera.d;
      // Shade point
      pixelValue = shade(Ray(camera.o, normalize(cameraRayDir)));
      // Convert shaded point to RGB value for display
      pixelColors[idx] = vec3(clamp(pixelValue.x),
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
