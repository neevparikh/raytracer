#pragma once
#include <eigen3/Eigen/Dense>
#include <random>
#include <yaml-cpp/yaml.h>
// #include <yaml-cpp/node/convert.h>

namespace YAML {
template <> struct convert<Eigen::Vector3f> {
  static Node encode(const Eigen::Vector3f &v) {
    Node node;
    node.push_back(v[0]);
    node.push_back(v[1]);
    node.push_back(v[2]);
    return node;
  }

  static bool decode(const Node &node, Eigen::Vector3f &v) {
    if (!node.IsSequence() || node.size() != 3) {
      return false;
    }
    v << node[0].as<double>(), node[1].as<double>(), node[2].as<double>();
    return true;
  }
};
}; // namespace YAML

namespace raytracer {
struct Random {
  Random() { this->_seed(); };

  inline float random_float() { return uniform_float(gen); };
  inline float random_normal() { return uniform_float(gen); };

private:
  inline static std::uniform_real_distribution<float> uniform_float{0.0, 1.0};
  inline static std::normal_distribution<float> normal_f{0.0, 1.0};
  inline static std::mt19937 gen;

  inline void _seed() { gen.seed(0); };
};
}; // namespace raytracer
