#include "raytracer/geometry.h"
#include "raytracer/utils.h"
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <iostream>

namespace raytracer {

Point Ray::at(double t) const { return origin + t * dir; };

double Sphere::intersection(const Ray &r) const {
  // quadratic: t^2 (b dot b) + 2t b dot v + v dot v - radius^2

  Point v = r.origin - center;
  auto a = 1; // r.dir.dot(r.dir); note that r.dir is unit so this is 1
  auto b = 2 * r.dir.dot(v);
  auto c = v.dot(v) - (radius * radius);
  auto disc = (b * b) - (4 * a * c);
  if (disc < 0) {
    return 0;
  } else if (disc == 0) {
    return -0.5 * b / a;
  } else {
    // this is numerically more stable:
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection

    auto disc_rt = sqrt(disc);
    auto q = (b > 0) ? -0.5 * (b + disc_rt) : -0.5 * (b - disc_rt);
    auto closest = std::min(q / a, c / q);
    return (closest > 0) ? closest : 0;
  };
};

Vector Sphere::get_normal(const Point &intersection_pt) const {
  auto normal = intersection_pt - center;
  return normal.normalized();
};

std::unique_ptr<Shape> get_shape(YAML::Node cfg) {
  std::string s = cfg["name"].as<std::string>();
  if (s == "sphere") {
    Point c = cfg["center"].as<Point>();
    return std::make_unique<Sphere>(
        Sphere{cfg["radius"].as<double>(), c, Color{1, 0, 0}});
  } else {
    // TODO is this error handling fine?
    throw std::runtime_error("Invalid config file");
  };
};
}; // namespace raytracer
