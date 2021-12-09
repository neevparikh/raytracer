#pragma once
#include <eigen3/Eigen/Dense>

using Color = Eigen::Vector3f;

Eigen::Vector3i convert_color_to_255(Color c);

const Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
const Eigen::IOFormat PPMFmt(4, 0, " ", " ", "", "");

void write_color_to_file(std::fstream &f, Eigen::Vector3i c);
