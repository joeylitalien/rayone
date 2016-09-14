/**
   A simple Monte Carlo path tracer for ECSE 689 Physically Based Rendering
   Fall 2016, McGill University - Prof. Derek Nowrouzezahrai

   Author: Joey Litalien <joeylitalien@gmail.com>
   Date: 09/2016

   Images are written in PPM format
   See http://netpbm.sourceforge.net/doc/ppm.html for more info
   Based on smallpt developed by Kevin Beason (2008)
*/

// main/pathtracer.cpp
#include "../core/pathtracer.h"

// Initialize Cornell box
// 3 materials available: DIFFuse, SPECular and REFractive
Sphere scene[] = {
  Sphere(1e5, Vec( 1e5+1,40.8,81.6), Vec(),Vec(.75,.25,.25),DIFF),  // Left
  Sphere(1e5, Vec(-1e5+99,40.8,81.6),Vec(),Vec(.25,.25,.75),DIFF),  // Right
  Sphere(1e5, Vec(50,40.8, 1e5),     Vec(),Vec(.75,.75,.75),DIFF),  // Back
  Sphere(1e5, Vec(50,40.8,-1e5+170), Vec(),Vec(),           DIFF),  // Front
  Sphere(1e5, Vec(50, 1e5, 81.6),    Vec(),Vec(.75,.75,.75),DIFF),  // Floor
  Sphere(1e5, Vec(50,-1e5+81.6,81.6),Vec(),Vec(.75,.75,.75),DIFF),  // Ceiling
  Sphere(16.5,Vec(27,16.5,47),       Vec(),Vec(1,1,1)*.999, DIFF),  // Mirror
  Sphere(16.5,Vec(73,16.5,78),       Vec(),Vec(1,1,1)*.999, DIFF),  // Glass
  Sphere(1.5, Vec(50,81.6-16.5,81.6),Vec(4,4,4)*100,  Vec(),DIFF)   // Light
};

// Scene renderer
Renderer *RNDR = new Renderer();

// Main rendering loop
// Render image seen from a camera and write image to PPM file
int main(int argc, char *argv[]) {
  static int w = 512, h = 384;                       // Image resolution
  static int spp = argc > 1 ? atoi(argv[1])/4 : 1;   // Samples per pixel (SPP)

  // tan(28 / 180 * pi) == 0.5317 serves as camera FoV
  Ray cam(Vec(50, 52, 295.6), Vec(0, -0.05, -1).Norm());   // Cam lookAt vector
  Vec cx = Vec(w * 0.5317 / h);                            // Cam x vector
  Vec cy = (cx % cam.d).Norm() * .5317;                    // Cam up vector

  Vec pixVal;                     // Sample color
  Vec *pixCol = new Vec[w * h];   // New pixel grid for image

  // Use OMP loop scheduler for parallel computing
  #pragma omp parallel for schedule(dynamic, 1) private(pixVal)

  // Loop over all image pixels
  for (int y = 0; y < h; y++) {
    fprintf(stderr, "\rRendering (%d SPP) %5.2f%%", spp*4, 100.*y / (h - 1));
    unsigned short Xi[3] = {0, 0, y * y * y};

    // Loop over each pixel, perform 2x2 subpixel sampling
    for (int x = 0; x < w; x++) {
      for (int sy = 0; sy < 2; sy++) {     // 2x2 subpixel rows
        int i = (h - y - 1) * w + x;
        for (int sx = 0; sx < 2; sx++) {   // 2x2 subpixel columns
          pixVal = Vec();                  // Initialize pixel
          // Create a tent filter at each subpixel
          double dx, dy; TentFilter(dx, dy, Xi);
          for (int sample = 0; sample < spp; sample++) {
            // Compute camera ray direction
            Vec camRayDir = cx * (((sx + .5 + dx) / 2 + x) / w - .5) +
                            cy * (((sy + .5 + dy) / 2 + y) / h - .5) + cam.d;
            // Shade pixel using radiance value
            // Camera rays are pushed forward to start in interior of vox
            pixVal = pixVal + RNDR->Radiance(scene, Ray(cam.o + camRayDir * 140,
                       camRayDir.Norm()), 0, Xi) * (1./spp);
          }
         // Convert shaded point to RGB value for display
          pixCol[i] = pixCol[i] + Vec(Clamp(pixVal.x),
                                      Clamp(pixVal.y),
                                      Clamp(pixVal.z)) * 0.25;
        }
      }
    }
  }

  // Write image as PPM Portable Bitmap Format
  FILE *f = fopen("image.ppm", "w");
  fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
  for (int p = 0; p < w * h; p++) {
    fprintf(f, "%d %d %d ", ToDisplayValue(pixCol[p].x),
                            ToDisplayValue(pixCol[p].y),
                            ToDisplayValue(pixCol[p].z));
  }
  fclose(f);         // Close file
  delete[] pixCol;   // Free allocated memory
  delete RNDR;
  return 0;
}
