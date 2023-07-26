#!/bin/sh

set -xe
gcc voronoi.c -o canvas.out
./canvas.out
feh --image-bg black out_voronoi.ppm
