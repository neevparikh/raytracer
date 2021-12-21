#include "raytracer/geometry.h"
#include "raytracer/utils.h"
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <optional>

namespace raytracer {

Point Ray::at(float t) const { return origin + t * dir; };

std::optional<float> Sphere::intersection(const Ray &r) const {
  /* Returns solution to quadratic: t^2 (b dot b) + 2t b dot v + v dot v -
   * radius^2
   *
   * returns smallest solution as float if and only if the solution is real and
   * positive. else returns null
   * */

  Point v = r.origin - center;
  auto a = 1; // r.dir.dot(r.dir); note that r.dir is unit so this is 1
  auto b = 2 * r.dir.dot(v);
  auto c = v.dot(v) - (radius * radius);
  auto disc = (b * b) - (4 * a * c);
  if (disc < 0) {
    return std::nullopt;
  } else if (disc == 0) {
    auto ans = -0.5 * b / a;
    if (ans > 0) {
      return ans;
    } else {
      return std::nullopt;
    };
  } else {
    // this is numerically more stable:
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection

    auto disc_rt = sqrt(disc);
    auto q = (b > 0) ? -0.5 * (b + disc_rt) : -0.5 * (b - disc_rt);
    auto s1 = q / a;
    auto s2 = c / q;
    auto closest = std::min(s1, s2);
    if (s1 > 0 && s2 > 0) {
      return closest;
    } else if (s1 < 0 && s2 < 0) {
      return std::nullopt;
    } else {
      return std::max(s1, s2);
    };
  };
};

const Vector Sphere::get_normal(const Point &intersection_pt) const {
  auto normal = intersection_pt - center;
  return normal.normalized();
};

std::unique_ptr<Shape> get_shape(YAML::Node cfg) {
  std::string s = cfg["name"].as<std::string>();
  if (s == "sphere") {
    return std::make_unique<Sphere>(Sphere{cfg["radius"].as<float>(),
                                           cfg["center"].as<Point>(),
                                           clamp(cfg["color"].as<Color>())});
  } else {
    // TODO is this error handling fine?
    throw std::runtime_error("Invalid config file");
  };
};
}; // namespace raytracer
