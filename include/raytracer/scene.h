#pragma once
#include "raytracer/camera.h"
#include "raytracer/geometry.h"
#include <eigen3/Eigen/Dense>
#include <functional>
#include <string>

namespace raytracer {
struct Image {
  std::string filename;
  int xres;
  int yres;
};

struct Scene {
  std::vector<std::unique_ptr<Shape>> shapes;
  Camera camera;
  Image img;
};

Scene load_scene(std::string config_filename);
}; // namespace raytracer
