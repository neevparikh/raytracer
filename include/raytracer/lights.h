#pragma once
#include "raytracer/colors.h"
#include "raytracer/geometry.h"
#include <eigen3/Eigen/Dense>

namespace raytracer {

struct Light {
  const Color color;
  const float intensity;
  const Point location;
};

struct DirectionalLight : Light {
  const Vector direction;
};

struct PointLight : Light {};

}; // namespace raytracer
