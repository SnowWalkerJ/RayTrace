#ifndef RAYTRACE_INCLUDE_VECTOR_H_
#define RAYTRACE_INCLUDE_VECTOR_H_
#include "impl/vector.h"
#include <algorithm>
namespace raytrace {
class Vector {
 public:
  constexpr Vector() : Vector(0.0, 0.0, 0.0) {}
  constexpr Vector(RT_FLOAT x, RT_FLOAT y, RT_FLOAT z) : m_data_(x, y, z) {}
  Vector(const Vector &) noexcept = default;
  Vector &operator=(const Vector &) noexcept = default;
  RT_FLOAT X() const { return m_data_.m_x; }
  RT_FLOAT Y() const { return m_data_.m_y; }
  RT_FLOAT Z() const { return m_data_.m_z; }
  Vector Truncate(RT_FLOAT min=0.0f, RT_FLOAT max=1.0f) const {
    return Vector(
        std::clamp(m_data_.m_x, min, max),
        std::clamp(m_data_.m_y, min, max),
        std::clamp(m_data_.m_z, min, max)
        );
  }
  RT_FLOAT dot(const Vector &v) const {
    return m_data_.dot(v.m_data_);
  }
  Vector cross(const Vector &v) const {
    return Vector(m_data_.cross(v.m_data_));
  }
  Vector Normalize() const {
    return Vector(m_data_.normalize());
  }
  RT_FLOAT Norm() const {
    return m_data_.norm();
  }
  RT_FLOAT Norm2() const {
    return m_data_.norm2();
  }
  std::pair<RT_FLOAT, RT_FLOAT> Decompose(const Vector &v1, const Vector &v2) const {
    RT_FLOAT a = v1.dot(v1), b = v1.dot(v2), d = v2.dot(v2);
    RT_FLOAT c = b;
    RT_FLOAT p = 1 / (a * d - b * c);
    RT_FLOAT a2 = d * p, b2 = -b * p, c2 = -c * p, d2 = a * p;
    RT_FLOAT xy1 = this->dot(v1), xy2 = this->dot(v2);
    RT_FLOAT component1 = a2 * xy1 + b2 * xy2,
             component2 = c2 * xy1 + d2 * xy2;
    if (std::fabs((component1 * v1 + component2 * v2 - *this).Norm()) >= 1e-5) {
      std::cout << (component1 * v1 + component2 * v2 - *this).Norm() << std::endl;
      assert(std::fabs((component1 * v1 + component2 * v2 - *this).Norm()) < 1e-5);
    }

    return {component1, component2};
  }
  mkInplaceAdd(Vector)
  mkInplaceSub(Vector)
  mkInplaceMul(Vector)
  mkInplaceDiv(Vector)
  mkNeg(Vector)
  mkAdd(Vector)
  mkSub(Vector)
  mkMul(Vector)
  mkDiv(Vector)
 protected:
  explicit Vector(const detail::vector3d &v) : m_data_(v) {}
 private:
  detail::vector3d m_data_;
};

inline std::ostream &operator<<(std::ostream &os, const Vector &v) {
  return os << "(" << v.X() << ", " << v.Y() << ", " << v.Z() << ')';
}

typedef Vector Point;
} // namespace raytrace
#endif //RAYTRACE_INCLUDE_VECTOR_H_
