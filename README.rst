Rayone 💡
========

Description
-----------------
*Rayone* (from French "Rayon") is a simple global illumination renderer that uses Monte Carlo techniques such as importance sampling, rejection sampling, and variance reduction to render simple scenes (e.g. Cornell Box). This path tracer is being developed using David Beason's `smallpt`_ as a starting point while remotely following the course `ECSE 689 Realistic Image Synthesis`_ by D. Nowrouzezahrai (McGill University, Fall 2016) and reading `Physically Based Rendering`_ by M. Pharr and G. Humphreys.

Features
--------
* Global illumination via unbiased Monte Carlo path tracing
* Modular code
* Multithreading using `OpenMP`_
* Soft shadows from diffuse luminaire
* Diffuse and specular BRDFs
* Antialiasing
* Ray-sphere intersection
* Cosine-weighted hemispherical importance sampling for diffuse reflection
* Phong cosine-power hemispherical importance sampling for specular reflection
* Russian roulette for path termination

Future Implementations
----------------------
* Refractive BRDF
* Ray-triangle intersection
* Motion blur
* Volumetric single scattering
* Environment map importance sampling
* Photon mapping

Current Known Issues
--------------------
* Random artifacts when using one specular sphere (bug also present in smallpt)
* Cannot retrieve radius of ``Sphere`` for ray hit since the scene is a ``Shape`` vector

.. _smallpt: http://www.kevinbeason.com/smallpt
.. _Physically Based Rendering: http://pbrt.org
.. _ECSE 689 Realistic Image Synthesis: http://www.cim.mcgill.ca/~derek/ecse689.html
.. _OpenMP: http://openmp.org/wp
