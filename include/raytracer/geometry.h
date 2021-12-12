#pragma once
#include <eigen3/Eigen/Dense>
#include <yaml-cpp/yaml.h>

namespace raytracer {
using Point = Eigen::Vector3f;
using Vector = Eigen::Vector3f;

struct Ray {
  // constructor
  Ray(const Point &orig, const Vector &direction) {
    origin = orig;
    dir = direction.normalized();
  };

  Point at(double t) const;

  Point origin;
  Vector dir;
};

struct Shape {
  virtual bool hits(const Ray &r) const = 0;
  virtual ~Shape() = default;
};

struct Sphere : public Shape {
  Sphere(const double r, const Point &c) {
    radius = r;
    center = c;
  };
  double radius;
  Point center;

  bool hits(const Ray &r) const;
};

std::unique_ptr<Shape> get_shape(YAML::Node cfg);
}; // namespace raytracer
