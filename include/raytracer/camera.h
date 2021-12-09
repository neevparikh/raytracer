#pragma once
#include <eigen3/Eigen/Dense>
#include "raytracer/geometry.h"

// Image
const auto aspect_ratio = 16.0 / 9.0;
const int im_width = 720;
const int im_height = static_cast<int>(im_width / aspect_ratio);

// Camera

const auto viewport_height = 2.0;
const auto viewport_width = viewport_height * aspect_ratio;
const auto focal_length = 1.0;


const auto origin = Point{0, 0, 0};
const auto viewport_x = Eigen::Vector3f{viewport_width, 0, 0};
const auto viewport_y = Eigen::Vector3f{0, viewport_height, 0};
const auto bottom_left = origin - (viewport_x / 2) - (viewport_y / 2) - Eigen::Vector3f{0, 0, focal_length};

