#include "raytracer/colors.h"
#include <fstream>

namespace raytracer {

Color clamp(const Color &c) { return c.cwiseMin(1).cwiseMax(0); };

Color255 convert_color_to_255(Color c) {
  c = clamp(c);
  c = c.array().pow(1 / 2.2); // gamma correction
  c *= 255.999;
  return c.cast<int>();
};

void write_color_to_file(std::fstream &f, Color255 c) {
  f << c.format(PPMFmt) << '\n';
};
}; // namespace raytracer
