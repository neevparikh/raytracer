#pragma once
#include "raytracer/colors.h"
#include "raytracer/geometry.h"
#include <eigen3/Eigen/Dense>

namespace raytracer {

struct Light {
  const Color color;
  const float intensity;
};

struct DirectionalLight : Light {
  const Vector direction;
};

struct PointLight : Light {
  const Point location;
};

}; // namespace raytracer
