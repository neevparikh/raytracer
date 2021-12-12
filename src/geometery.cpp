#include "raytracer/geometry.h"
#include "raytracer/utils.h"
#include <cmath>
#include <eigen3/Eigen/Dense>

namespace raytracer {

Point Ray::at(double t) const { return origin + t * dir; };

bool Sphere::hits(const Ray &r) const {
  // quadratic: t^2 (b dot b) + 2t b dot v + v dot v - radius^2

  Point v = r.origin - center;
  auto a = r.dir.dot(r.dir);
  auto b = 2 * r.dir.dot(v);
  auto c = v.dot(v) - pow(radius, 2);
  return (pow(b, 2) - (4 * a * c)) > 0;
};

std::unique_ptr<Shape> get_shape(YAML::Node cfg) {
  std::string s = cfg["name"].as<std::string>();
  if (s == "sphere") {
    Point c = cfg["center"].as<Point>();
    return std::make_unique<Sphere>(Sphere{cfg["radius"].as<double>(), c});
  } else {
    // TODO is this error handling fine?
    throw std::runtime_error("Invalid config file");
  };
};
}; // namespace raytracer
