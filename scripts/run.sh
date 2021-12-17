#!/usr/bin/env zsh

./scripts/debug.sh && time ./build/debug/raytracer && feh tmp_output/image.ppm
