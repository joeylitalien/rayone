# Rayon

### Small description
*Rayon* is a simple global illumination renderer. It uses Monte Carlo techniques such as importance sampling, rejection sampling, and variance reduction to render a simple scene (Cornell Box). This path tracer is being developed based on David Beason's [smallpt] while remotely following the course [ECSE 689 Physically Based Rendering][website] at McGill University (Fall 2016, D. Nowrouzezahrai).

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
* 

### To do
* Refractive BRDF
* Ray-triangle intersection
* Motion blur
* Volumetric single scattering
* Environment map importance sampling
* Photon mapping on surfaces

[smallpt]: http://www.kevinbeason.com/smallpt
[website]: http://www.cim.mcgill.ca/~derek/ecse689.html
