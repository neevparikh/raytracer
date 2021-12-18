#include "raytracer/scene.h"
#include "raytracer/camera.h"
#include "raytracer/colors.h"
#include "raytracer/raytracer.h"
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
      static_cast<float>(xres),
      static_cast<float>(yres),
      config["camera"]["fov"].as<float>(),
      config["camera"]["roll"].as<float>(),
      config["camera"]["location"].as<Point>(),
      config["camera"]["direction"].as<Vector>(),
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
      .config = config,
  };
  return scn;
};

Color Scene::background(int x, int y) {
  auto w = camera.img_x;
  auto h = camera.img_y;
  /* auto a = static_cast<float>(x) - w / 2; */
  /* auto b = static_cast<float>(y) - (h * 5.65); */
  /* auto r = 5 * h; */
  /* Color c; */
  /* if (a * a + b * b < r * r) { */
  /*   c = Color{0.8, 1, 0.8}; */
  /* } else { */
  /*   c = Color{0.8, 0.8, 1}; */
  /* } */
  /* return c; */
  auto l = [](float a, float b) {
    return 1 - pow((std::abs(static_cast<float>(a) - (b / 2)) / (b / 2)), 0.9);
  };
  if (rng.random_float() < 0.005) {
    return Color{0.8, 0.8, 0.85};
  } else {
    auto v = (l(x, w) + l(y, h)) / 2;
    return 0.25 * Color{v, v, v};
  };
};
}; // namespace raytracer
