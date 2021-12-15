#include "raytracer/colors.h"
#include <fstream>

namespace raytracer {
Color255 convert_color_to_255(Color c) {
  c = c.cwiseMin(1).cwiseMax(0);
  c *= 255.999;
  return c.cast<int>();
};

void write_color_to_file(std::fstream &f, Color255 c) {
  f << c.format(PPMFmt) << '\n';
};
}; // namespace raytracer
