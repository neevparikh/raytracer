#include "raytracer/camera.h"
#include "raytracer/colors.h"
#include "raytracer/geometry.h"
#include <fstream>
#include <iostream>
#include <string>

void render(std::string filepath) {
  std::fstream img;
  img.open(filepath, std::ios::out);
  img << "P3\n" << im_width << ' ' << im_height << "\n255\n";

  for (int j = im_height; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

    for (int i = 0; i < im_width; ++i) {
      Color c = {double(i) / (im_width - 1), double(j) / (im_height - 1), 0.25};
      write_color_to_file(img, convert_color_to_255(c));
    }
  }
  img.close();
};

int main() { render("tmp_output/image.ppm"); }
