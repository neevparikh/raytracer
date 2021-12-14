#pragma once
#include "raytracer/camera.h"
#include "raytracer/colors.h"
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

  Color background(int x, int j);
};

Scene load_scene(std::string config_filename);
}; // namespace raytracer
