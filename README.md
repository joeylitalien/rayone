# Rayono

![](https://joeylitalien.github.io/assets/rayono.png)

### Small description
*Rayono* is a simple global illumination renderer that uses Monte Carlo techniques such as importance sampling, rejection sampling, and variance reduction to render simple scenes (e.g. Cornell Box). This path tracer is being developed based on David Beason's [smallpt] while remotely following the course [ECSE 689 Realistic Image Synthesis][website] by D. Nowrouzezahrai (McGill University, Fall 2016) and reading [Physically Based Rendering][pbrt] by M. Pharr and G. Humphreys.

### Features
* Global illumination via unbiased Monte Carlo path tracing
* Modular code
* Multithreading using OpenMP
* Soft shadows from diffuse luminaire
* Diffuse and specular BRDFs
* Antialiasing
* Ray-sphere intersection
* Cosine-weighted hemispherical importance sampling for diffuse reflection
* Phong cosine-power hemispherical importance sampling for specular reflection
* Russian roulette for path termination


### To do
* Refractive BRDF
* Ray-triangle intersection
* Motion blur
* Volumetric single scattering
* Environment map importance sampling
* Photon mapping

[smallpt]: http://www.kevinbeason.com/smallpt
[pbrt]: http://pbrt.org
[website]: http://www.cim.mcgill.ca/~derek/ecse689.html
