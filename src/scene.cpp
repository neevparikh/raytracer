#include "raytracer/scene.h"
#include "raytracer/camera.h"
#include "raytracer/colors.h"
#include "raytracer/lights.h"
#include "raytracer/raytracer.h"
#include "raytracer/utils.h"
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

namespace raytracer {

std::unique_ptr<Light> get_light(const YAML::Node cfg) {
  if (cfg["name"].as<std::string>() == "point") {
    return std::make_unique<PointLight>(PointLight{
        {
            cfg["color"].as<Color>(),
            cfg["intensity"].as<float>(),
            cfg["location"].as<Point>(),
        },
    });
  } else if (cfg["name"].as<std::string>() == "directional") {
    return std::make_unique<DirectionalLight>(DirectionalLight{
        {
            cfg["color"].as<Color>(),
            cfg["intensity"].as<float>(),
            cfg["location"].as<Point>(),
        },
        cfg["direction"].as<Vector>(),
    });
  } else {
    throw std::runtime_error("Invalid light type in config file");
  };
};

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

  std::vector<std::unique_ptr<Light>> lights;

  YAML::Node light_names = config["scene"]["lights"];

  assert(light_names.IsSequence());
  for (auto name : light_names) {
    auto p = get_light(name);
    lights.push_back(std::move(p));
  }

  Scene scn = Scene{
      .shapes = std::move(shapes),
      .lights = std::move(lights),
      .camera = cam,
      .img = img,
      .config = config,
  };
  return scn;
};

Color Scene::background(int x, int y) {
  auto w = camera.img_x;
  auto h = camera.img_y;
  auto m = std::min(w, h);
  auto l = [m](float a, float b) {
    return 1 - pow((std::min(std::abs(static_cast<float>(a) - (b / 2)), m / 2) /
                    (m / 2)),
                   0.3);
  };
  if (rng.random_float() < 0.005) {
    return Color{0.8, 0.8, 0.85};
  } else {
    float v = (l(x, w) + l(y, h)) / 2;
    return 0.02 * Color{v, v, v};
  };
};
}; // namespace raytracer
