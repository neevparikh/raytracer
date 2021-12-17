#include "raytracer/camera.h"
#include "raytracer/geometry.h"
#include <eigen3/Eigen/Dense>
#include <iostream>

namespace raytracer {

const Vector Camera::pixel_to_world_space(float x, float y) {
  Vector v = x * axis_u - y * axis_v + pixel_to_camera_w;
  return v;
};

const Vector Camera::camera_vec_to_world(const Vector &v) {
  return camera_to_world * v;
};

const Eigen::Affine3f Camera::_construct_cam_matrix() {
  Eigen::Affine3f m;
  Vector z = -direction;
  Vector x = Vector{1, 0, 0};
  Vector y;

  if (z == Vector{0, 1, 0}) {
    y = Vector{0, 0, -1};
  } else if (z == Vector{0, -1, 0}) {
    y = Vector{0, 0, 1};
  } else {
    x = Vector{0, 1, 0}.cross(z);
    y = z.cross(x);
  };

  m.matrix().block<3, 1>(0, 0) << x;
  m.matrix().block<3, 1>(0, 1) << y;
  m.matrix().block<3, 1>(0, 2) << z;
  m.matrix().block<3, 1>(0, 3) << location;
  m.matrix().row(3) << 0, 0, 0, 1;

  Eigen::AngleAxisf r = Eigen::AngleAxisf{roll, z};

  return r * m;
};
}; // namespace raytracer
