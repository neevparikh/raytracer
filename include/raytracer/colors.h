#pragma once
#include <eigen3/Eigen/Dense>

namespace raytracer {
using Color = Eigen::Vector3f;
using Color255 = Eigen::Vector3i;

Color clamp(const Color &c);
Color255 convert_color_to_255(Color c);

const Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
const Eigen::IOFormat PPMFmt(4, 0, " ", " ", "", "");

void write_color_to_file(std::fstream &f, Color255 c);
}; // namespace raytracer
