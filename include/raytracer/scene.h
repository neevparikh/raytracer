#pragma once
#include "raytracer/camera.h"
#include "raytracer/colors.h"
#include "raytracer/geometry.h"
#include "raytracer/raytracer.h"
#include <eigen3/Eigen/Dense>
#include <functional>
#include <string>
#include <yaml-cpp/yaml.h>

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
  YAML::Node config;

  Color background(int x, int j);
};

Scene load_scene(std::string config_filename);
}; // namespace raytracer
