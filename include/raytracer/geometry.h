#pragma once
#include "raytracer/colors.h"
#include <eigen3/Eigen/Dense>
#include <yaml-cpp/yaml.h>

namespace raytracer {
using Point = Eigen::Vector3f;
using Vector = Eigen::Vector3f;
using Matrix = Eigen::Matrix4f;

struct Ray {
  // constructor
  Ray(const Point &orig, const Vector &direction) {
    origin = orig;
    dir = direction.normalized();
  };

  Point at(float t) const;

  Point origin;
  Vector dir;
};

struct Shape {
  const Color material_color;
  virtual float intersection(const Ray &r) const = 0;
  virtual Vector get_normal(const Point &intersection_pt) const = 0;
  virtual ~Shape() = default;
};

struct Sphere : public virtual Shape {
  Sphere(const float r, const Point &c, const Color &color)
      : radius{r}, center{c}, material_color{color} {};
  const float radius;
  const Point center;
  const Color material_color;

  float intersection(const Ray &r) const override;
  Vector get_normal(const Point &intersection_pt) const override;
};

std::unique_ptr<Shape> get_shape(YAML::Node cfg);
}; // namespace raytracer
