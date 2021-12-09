#include <fstream>
#include "raytracer/colors.h"


Eigen::Vector3i convert_color_to_255(Color c) { 
  Color v = 255.999 * c;
  return v.cast<int>();
};

void write_color_to_file(std::fstream &f, Eigen::Vector3i c) {
  f << c.format(PPMFmt) << '\n';
};
