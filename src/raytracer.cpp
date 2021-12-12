#include "raytracer/camera.h"
#include "raytracer/colors.h"
#include "raytracer/geometry.h"
#include "raytracer/scene.h"
#include "raytracer/utils.h"
#include <fstream>
#include <iostream>
#include <memory>
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

    for (int j = yres; j >= 0; --j) {
      for (int i = 0; i < xres; ++i) {
        auto u = static_cast<double>(i) / (xres - 1);
        auto v = static_cast<double>(j) / (yres - 1);
        Color c = {0.1, v, u};

        Vector d = scn.camera.bottom_left + u * scn.camera.viewport_x +
                   v * scn.camera.viewport_y - scn.camera.origin;
        Ray r = Ray{scn.camera.origin, d};

        for (auto &shp : scn.shapes) {
          if (shp->hits(r)) {
            c = {0.5, 0, 0};
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
