#pragma once
#include "raytracer/geometry.h"
#include <eigen3/Eigen/Dense>

// Camera
namespace raytracer {
struct Camera {
  const float aspect_ratio;

  const float focal_length = 1.0;

  const float viewport_height = 2.0;
  const float viewport_width = viewport_height * aspect_ratio;

  const Point origin = Point{0, 0, 0};
  const Vector viewport_x = Vector{viewport_width, 0, 0};
  const Vector viewport_y = Vector{0, viewport_height, 0};
  const Vector bottom_left =
      origin - (viewport_x / 2) - (viewport_y / 2) - Vector{0, 0, focal_length};
};
}; // namespace raytracer
