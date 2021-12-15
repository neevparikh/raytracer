#include "raytracer/camera.h"
#include "raytracer/colors.h"
#include "raytracer/geometry.h"
#include "raytracer/scene.h"
#include "raytracer/utils.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <cmath>
#include <string>
#include <yaml-cpp/yaml.h>

namespace raytracer {

void render(std::string config_filepath) {

  try {
    Scene scn = load_scene(config_filepath);
    int xres = scn.img.xres;
    int yres = scn.img.yres;

    std::fstream img;
    img.open(scn.img.filename, std::ios::out);
    img << "P3\n" << xres << ' ' << yres << "\n255\n";

    for (int j = 0; j < yres; ++j) {
      for (int i = 0; i < xres; ++i) {
        Vector d = scn.camera.pixel_to_world_space(i, j);
        Ray r = Ray{scn.camera.location, d};
        Color c = scn.background(i, j);

        for (auto &shp : scn.shapes) {
          // TODO only render the one with smallest t
          auto t = shp->intersection(r);
          if (t > 0) {
            auto n = shp->get_normal(r.at(t));
            c = (shp->material_color) * std::max(static_cast<double>(n.dot(-r.dir)), 0.0);
          };
        };

        write_color_to_file(img, convert_color_to_255(c));
      }
    }
    img.close();
  } catch (std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
  };
};
}; // namespace raytracer
