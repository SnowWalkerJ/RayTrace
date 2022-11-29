#ifndef RAYTRACE_INCLUDE_VECTOR_H_
#define RAYTRACE_INCLUDE_VECTOR_H_
#include "impl/vector.h"
#include <algorithm>
#include <cassert>
#include <utility>
namespace raytrace {

namespace {
template<typename>
struct vec;

template<>
struct vec<float> {
  using type = Eigen::Vector3f;
};

template<>
struct vec<double> {
  using type = Eigen::Vector3d;
};
}
using Vector = typename vec<RT_FLOAT>::type;

template<typename D1, typename D2>
[[nodiscard]] auto cross(const Eigen::MatrixBase<D1> &v1, const Eigen::MatrixBase<D2> &v2) {
  RT_FLOAT x_ = v1.y() * v2.z() - v1.z() * v2.y(),
           y_ = v1.z() * v2.x() - v1.x() * v2.z(),
           z_ = v1.x() * v2.y() - v1.y() * v2.x();
  return Vector(x_, y_, z_);
}

template<typename D, typename D1, typename D2>
[[nodiscard]] std::pair<RT_FLOAT, RT_FLOAT> decompose(const Eigen::MatrixBase<D> &v, const Eigen::MatrixBase<D1> &v1, const Eigen::MatrixBase<D2> &v2) {
  RT_FLOAT a = v1.dot(v1), b = v1.dot(v2), d = v2.dot(v2);
  RT_FLOAT c = b;
  RT_FLOAT p = 1 / (a * d - b * c);
  RT_FLOAT a2 = d * p, b2 = -b * p, c2 = -c * p, d2 = a * p;
  RT_FLOAT xy1 = v.dot(v1), xy2 = v.dot(v2);
  RT_FLOAT component1 = a2 * xy1 + b2 * xy2,
      component2 = c2 * xy1 + d2 * xy2;

  return {component1, component2};
}

template<typename Derived>
inline std::ostream &operator<<(std::ostream &os, const Eigen::MatrixBase<Derived> &v) {
  return os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ')';
}

typedef Vector Point;
} // namespace raytrace
#endif //RAYTRACE_INCLUDE_VECTOR_H_
