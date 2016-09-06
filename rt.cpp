/**
 *   @file     rt.cpp
 *   @author   Derek Nowrouzezahrai & Joey Litalien
 *   @version  1.1
 *
 *   A minimalistic ray tracer for the course ECSE 689 Physically Based
 *   Rendering Fall 2016 at McGill University.
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


/**
 *   Vector structure
 *   Implement vectors and common operations
 */
struct Vec {
  double x, y, z;   // Vector v = (x, y, z)

  // Default constructor
  Vec(double x_= 0, double y_= 0, double z_= 0){ x = x_; y = y_; z = z_; }

  // Operator overloading (add, subtract, multiply by scalar)
  Vec operator+(const Vec &b) const { return Vec(x + b.x, y + b.y, z + b.z); }
  Vec operator-(const Vec &b) const { return Vec(x - b.x, y - b.y, z - b.z); }
  Vec operator*(double b) const { return Vec(x * b, y * b, z * b); }

  // Vector cross product
  Vec operator%(Vec&b) {
    return Vec(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
  }

  // Vector dot product
  double dot(const Vec &b) const { return x * b.x + y * b.y + z * b.z; }

  // Component-wise vector multiplication
  Vec mult(const Vec &b) const { return Vec(x * b.x, y * b.y, z * b.z); }

  // Vector normal
  Vec& norm() { return *this = *this * (1.0 / sqrt(x * x + y * y + z * z)); }
};


/**
 *   Ray structure
 *   Implement a basic ray with origin o and direction d
 */
struct Ray { Vec o, d; Ray(Vec o_, Vec d_) : o(o_), d(d_) {} };


/**
 *   Sphere structure
 *   Implement sphere shapes and interesction methods
 */
struct Sphere {
  double r;   // Sphere radius
  Vec p, e, c;   // p = Sphere center; e & c undefined

  // Default constructor
  Sphere(double r_, Vec p_, Vec e_, Vec c_): r(r_), p(p_), e(e_), c(c_) {}

  // Compute geometric intersection of sphere with casted ray
  // Return t value of ray interesection with sphere (r = o + td)
  double intersect(const Ray &ray) const {
    Vec op = p - ray.o;   // Vector from ray origin to sphere center
    double t, eps = 1e-4;   // Small, nonzero value to handle rounding errors
    double b = op.dot(ray.d);   // Project op onto d
    double det = b * b - op.dot(op) + r * r;   // Pythagorean theorem

    if (det < 0) return 0;   // Two complex roots, no interesections
    else det = sqrt(det);   // Two real roots, take square root

    // Return closest intersection
    return (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
  }
};


// Construct simple scene with 3 spheres and 5 walls
Sphere spheres[] = {
  Sphere(1e5,  Vec(1e5 + 1, 40.8, 81.6), Vec(0, 0, 0), Vec(.75, .25, .25)),
  Sphere(1e5,  Vec(-1e5 + 99, 40.8, 81.6), Vec(0, 0, 0), Vec(.25, .25, .75)),
  Sphere(1e5,  Vec(50, 40.8, 1e5), Vec(0, 0, 0), Vec(.75, .75, .75)),
  Sphere(1e5,  Vec(50, 1e5, 81.6), Vec(0, 0, 0), Vec(.75, .75, .75)),
  Sphere(1e5,  Vec(50, -1e5 + 81.6, 81.6), Vec(0, 0, 0), Vec(.75, .75, .75)),
  Sphere(16.5, Vec(27, 16.5, 47), Vec(0, 0, 0), Vec(.999, .999, .999)),
  Sphere(16.5, Vec(73, 16.5, 78), Vec(0, 0, 0), Vec(.999, .999, .999) ),
  Sphere(10.5, Vec(50, 68.6 - .27, 81.6), Vec(400, 400, 400), Vec(1, 1, 1))
};


// Restrict x value to [0,1] interval
inline double clamp(double x) { return x < 0 ? 0 : x > 1 ? 1 : x; }


// Convert value to RGB color for file writing
inline int toDisplayValue(double x) {
  return int(pow(clamp(x), 1.0/2.2 ) * 255 + .5);
}


// Intersect ray with scene
inline bool intersect(const Ray &r, double &t, int &id) {
  double n = sizeof(spheres) / sizeof(Sphere);
  double d, inf = t = 1e20;

  for (int i = int(n); i--;) {   // Check interesection against all spheres
    if ((d = spheres[i].intersect(r)) && d < t) {   // Intersection found
      t = d;   // Update t parameter
      id = i;   // Store sphere ID
    }
  }

  return t < inf;
}


// Vertex shader
Vec shade(const Ray &r) {
  double t;
  int id = 0;
  if (!intersect(r, t, id))   // If no interesections, return empty vector
    return Vec();

  const Sphere &obj = spheres[id];   // Else, get sphere ID
  Vec x = r.o + r.d * t;   // Retrieve point on sphere
  Vec n = (x - obj.p).norm();   // Compute normal at this point

  return n + obj.c;   // Return shading value
}


/**
 *   Main render loop
 *   Render image seen from a camera and write image to PPM file
 */
int main(int argc, char *argv[]) {
  int w = 512, h = 384;   // Set display resolution

  // tan( 30 / 180.0 * M_PI ) == 0.57735
  Ray camera(Vec(50, 50, 275.0), Vec(0, -0.05, -1).norm());   // New camera
  Vec cx = Vec(w * 0.57735 / h, 0., 0.);   // Camera x vector
  Vec cy = (cx % camera.d).norm() * 0.57735;   // Camera up vector

  Vec pixelValue, *pixelColors = new Vec[w * h];   // New pixel grid

  // Tell compiler to use OMP loop scheduler for parallel computing
  #pragma omp parallel for schedule(dynamic, 1) private(pixelValue)

  // Assign value to each pixel in grid
  for (int y = 0; y < h; y++) {
    fprintf(stderr, "\r%5.2f%%", 100.*y / (h - 1));
    for (int x = 0; x < w; x++) {
      int idx = (h - y - 1) * w + x;
      pixelValue = Vec();
      Vec cameraRayDir = cx * (double(x) / w - .5) +
                         cy * (double(y) / h - .5) +
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
  delete pixelColors;   // Free allocated memory
  return 0;
}
