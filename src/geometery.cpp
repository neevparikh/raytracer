#include <eigen3/Eigen/Dense>
#include "raytracer/geometry.h"


Point Ray::at(double t) const {
  return origin + t * dir;
};
