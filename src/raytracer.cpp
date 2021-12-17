#include "raytracer/camera.h"
#include "raytracer/colors.h"
#include "raytracer/geometry.h"
#include "raytracer/scene.h"
#include "raytracer/utils.h"
#include <algorithm>
#include <cmath>
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

    int aa_num_samples =
        scn.config["performance"]["antialiasing_samples"].as<int>();
    int aa_grid_size =
        static_cast<int>(sqrtf(static_cast<float>(aa_num_samples)));

    bool multiprocessing =
        scn.config["performance"]["multiprocessing"].as<bool>();

    Random rng = Random{};

    Color colors[xres][yres];
#pragma omp parallel for collapse(2) schedule(dynamic) if (multiprocessing)
    for (int j = 0; j < yres; ++j) {
      for (int i = 0; i < xres; ++i) {
        Color c = {0, 0, 0};
        for (int sub_i = 0; sub_i < aa_grid_size; ++sub_i) {
          for (int sub_j = 0; sub_j < aa_grid_size; ++sub_j) {
            Vector d = scn.camera.pixel_to_world_space(
                i + sub_i / aa_grid_size + rng.random_normal() / aa_grid_size,
                j + sub_j / aa_grid_size + rng.random_normal() / aa_grid_size);
            Ray r = Ray{scn.camera.location, d};

            auto closest_shp_iterator = std::min_element(
                scn.shapes.begin(), scn.shapes.end(),
                [r](const std::unique_ptr<Shape> &shp1,
                    const std::unique_ptr<Shape> &shp2) -> bool {
                  return shp1->intersection(r) < shp2->intersection(r);
                });

            auto closest_shp = (*closest_shp_iterator).get();
            assert(closest_shp);

            if (auto t = closest_shp->intersection(r); t > 0) {
              auto n = closest_shp->get_normal(r.at(t));
              c += (closest_shp->material_color) *
                   std::max(static_cast<float>(n.dot(-r.dir)), 0.0f);
            } else {
              c += scn.background(i, j);
            };
          }
        }
        c /= aa_num_samples;
        colors[i][j] = c;
      }
    }
    for (int j = 0; j < yres; ++j) {
      for (int i = 0; i < xres; ++i) {
        write_color_to_file(img, convert_color_to_255(colors[i][j]));
      }
    }
    img.close();
  } catch (std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
  };
};
}; // namespace raytracer
