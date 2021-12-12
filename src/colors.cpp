#include "raytracer/colors.h"
#include <fstream>

namespace raytracer {
Color255 convert_color_to_255(Color c) {
  Color v = 255.999 * c;
  return v.cast<int>();
};

void write_color_to_file(std::fstream &f, Color255 c) {
  f << c.format(PPMFmt) << '\n';
};
}; // namespace raytracer
