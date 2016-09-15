#!/bin/bash
# 'brew install gnu-time' for GNU time
# 'brew install imagemagick' for ImageMagick (handles PPM files)

gtime -f "\nElapsed time %E" ./rayone "$1"
mv image.ppm ../../img/cornell-$1.ppm
display ../../img/cornell-$1.ppm
