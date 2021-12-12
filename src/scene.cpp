#include "raytracer/scene.h"
#include "raytracer/camera.h"
#include "raytracer/utils.h"
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

using std::cout;
namespace raytracer {
Scene load_scene(std::string config_filename) {
  YAML::Node config = YAML::LoadFile(config_filename);

  assert(config["image"].IsMap());
  int xres = config["image"]["xres"].as<int>();
  int yres = config["image"]["yres"].as<int>();

  const float aspect_ratio =
      static_cast<float>(xres) / static_cast<float>(yres);

  Camera cam = Camera{.aspect_ratio = aspect_ratio};
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
}; // namespace raytracer
