#!/usr/bin/env zsh

./scripts/debug.sh && time ./build/debug/raytracer && feh --force-aliasing tmp_output/image.ppm
