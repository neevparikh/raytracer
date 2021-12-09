#pragma once
#include <eigen3/Eigen/Dense>

using Point = Eigen::Vector3f;

class Ray {
  public:
    // constructor
    Ray(const Point &orig, const Eigen::Vector3f &direction) {
      origin = orig;
      dir = direction.normalized();
    };

    Point at(double t) const;  

  private:
    Point origin;
    Eigen::Vector3f dir;
};
