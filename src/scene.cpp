#include "raytracer/scene.h"
#include "raytracer/camera.h"
#include "raytracer/colors.h"
#include "raytracer/utils.h"
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

namespace raytracer {
Scene load_scene(std::string config_filename) {
  YAML::Node config = YAML::LoadFile(config_filename);

  assert(config["image"].IsMap());
  int xres = config["image"]["xres"].as<int>();
  int yres = config["image"]["yres"].as<int>();

  Camera cam = Camera{
      .img_x = static_cast<float>(xres),
      .img_y = static_cast<float>(yres),
      .fov_degrees = config["camera"]["fov"].as<float>(),
      .roll_degrees = config["camera"]["roll"].as<float>(),
      .location = config["camera"]["location"].as<Point>(),
      .direction = config["camera"]["direction"].as<Vector>(),
  };
  Image img = Image{
      config["image"]["filename"].as<std::string>(),
      xres,
      yres,
  };

  std::vector<std::unique_ptr<Shape>> shapes;

  YAML::Node shape_names = config["scene"]["shapes"];

  assert(shape_names.IsSequence());
  for (auto name : shape_names) {
    auto p = get_shape(name);
    shapes.push_back(std::move(p));
  }

  Scene scn = Scene{
      .shapes = std::move(shapes),
      .camera = cam,
      .img = img,
  };
  return scn;
};

Color Scene::background(int x, int y) {
  auto w = camera.img_x;
  auto h = camera.img_y;
  auto a = static_cast<double>(x) - w / 2;
  auto b = static_cast<double>(y) - (h * 5.65);
  auto r = 5 * h;
  Color c;
  if (a * a + b * b < r * r) {
    c = Color{0.8, 1, 0.8};
  } else {
    c = Color{0.8, 0.8, 1};
  }
  return c;
};
}; // namespace raytracer
