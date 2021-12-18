#pragma once
#include "raytracer/geometry.h"
#include <cmath>
#include <eigen3/Eigen/Dense>

// Camera TODO: move to config
namespace raytracer {
struct Camera {

  // from config

  Camera(const float img_x, const float img_y, const float fov_degrees,
         const float roll_degrees, const Point location, const Vector direction)
      : img_x{img_x}, img_y{img_y}, fov_degrees{fov_degrees},
        roll_degrees{roll_degrees}, location{location},
        direction{direction.normalized()} {};

  const float img_x;
  const float img_y;
  const float fov_degrees;
  const float roll_degrees;
  const Point location;
  const Vector direction;

  const float aspect_ratio = img_x / img_y;

  const float fov = fov_degrees * (M_PI / 180.0);
  const float roll = roll_degrees * (M_PI / 180.0);

  const Point origin = Point{0, 0, 0};

  const Eigen::Affine3f camera_to_world = _construct_cam_matrix();

  const Vector axis_u = camera_to_world.matrix().col(0).head(3);
  const Vector axis_v = camera_to_world.matrix().col(1).head(3);
  const Vector axis_w = camera_to_world.matrix().col(2).head(3);
  const Vector pixel_to_camera_w = (-img_x / 2) * axis_u +
                                   (img_y / 2) * axis_v -
                                   ((img_y / 2) / tan(fov / 2)) * axis_w;

  const Vector pixel_to_world_space(float x, float y);
  const Vector camera_vec_to_world(const Vector &v);

private:
  const Eigen::Affine3f _construct_cam_matrix();
};
}; // namespace raytracer
