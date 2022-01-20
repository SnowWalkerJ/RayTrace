#ifndef RAYTRACE_INCLUDE_IMPL_VECTOR_H_
#define RAYTRACE_INCLUDE_IMPL_VECTOR_H_
#include "common.h"
#include <cmath>
#include <cstddef>
namespace raytrace::detail {
struct vector3d {
  RT_FLOAT m_x, m_y, m_z;
  constexpr vector3d(RT_FLOAT x, RT_FLOAT y, RT_FLOAT z) {
    m_x = x;
    m_y = y;
    m_z = z;
  }
  explicit constexpr vector3d(RT_FLOAT v) : vector3d(v, v, v) {}
  vector3d(const vector3d &) noexcept = default;
  vector3d &operator=(const vector3d &) noexcept = default;
  vector3d &operator*=(RT_FLOAT n) {
    m_x *= n;
    m_y *= n;
    m_z *= n;
    return *this;
  }
  vector3d &operator/=(RT_FLOAT n) {
    m_x /= n;
    m_y /= n;
    m_z /= n;
    return *this;
  }
  vector3d &operator+=(const vector3d &v) {
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
    return *this;
  }
  vector3d &operator-=(const vector3d &v) {
    m_x -= v.m_x;
    m_y -= v.m_y;
    m_z -= v.m_z;
    return *this;
  }
  vector3d operator-() const {
    return {-m_x, -m_y, -m_z};
  }
  RT_FLOAT norm2() const {
    return dot(*this);
  }
  RT_FLOAT norm() const {
    return std::sqrt(norm2());
  }
  vector3d normalize() const {
    RT_FLOAT n = norm();
    return vector3d(
        m_x / n,
        m_y / n,
        m_z / n
    );
  }
  RT_FLOAT dot(const vector3d &other) const {
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
  }
  vector3d cross(const vector3d &other) const {
    RT_FLOAT x = m_y * other.m_z - m_z * other.m_y,
          y = m_z * other.m_x - m_x * other.m_z,
          z = m_x * other.m_y - m_y * other.m_x;
    return vector3d(x, y, z);
  }
};

inline vector3d operator+(const vector3d &v1, const vector3d &v2) {
  return vector3d(
      v1.m_x + v2.m_x,
      v1.m_y + v2.m_y,
      v1.m_z + v2.m_z
      );
}
inline vector3d operator-(const vector3d &v1, const vector3d &v2) {
  return vector3d(
      v1.m_x - v2.m_x,
      v1.m_y - v2.m_y,
      v1.m_z - v2.m_z
      );
}
inline vector3d operator*(const vector3d &v1, const vector3d &v2) {
  return vector3d(
      v1.m_x * v2.m_x,
      v1.m_y * v2.m_y,
      v1.m_z * v2.m_z
      );
}
inline vector3d operator/(const vector3d &v1, const vector3d &v2) {
  return vector3d(
      v1.m_x / v2.m_x,
      v1.m_y / v2.m_y,
      v1.m_z / v2.m_z
      );
}
inline vector3d operator*(const vector3d &v1, RT_FLOAT n) {
  return vector3d(
      v1.m_x * n,
      v1.m_y * n,
      v1.m_z * n
      );
}
inline vector3d operator/(const vector3d &v1, RT_FLOAT n) {
  return vector3d(
      v1.m_x / n,
      v1.m_y / n,
      v1.m_z / n
      );
}
inline vector3d operator*(RT_FLOAT n, const vector3d &v1) {
  return vector3d(
      v1.m_x * n,
      v1.m_y * n,
      v1.m_z * n
      );
}
} // namespace raytrace

#define mkAdd(cls) inline friend cls operator+(const cls &x1, const cls &x2) { return cls(x1.m_data_ + x2.m_data_); }
#define mkSub(cls) inline friend cls operator-(const cls &x1, const cls &x2) { return cls(x1.m_data_ - x2.m_data_); }
#define mkMul(cls) inline friend cls operator*(const cls &x, RT_FLOAT n) { return cls(x.m_data_ * n); } \
                   inline friend cls operator*(RT_FLOAT n, const cls &x) { return cls(x.m_data_ * n); }
#define mkDiv(cls) inline friend cls operator/(const cls &x, RT_FLOAT n) { return cls(x.m_data_ / n); }
#define mkNeg(cls) inline cls operator-() const { return cls(-this->m_data_); }
#define mkInplaceAdd(cls) cls &operator+=(const cls &x) { m_data_ += x.m_data_; return *this; }
#define mkInplaceSub(cls) cls &operator-=(const cls &x) { m_data_ -= x.m_data_; return *this; }
#define mkInplaceMul(cls) cls &operator*=(RT_FLOAT n) { m_data_ *= n; return *this; };
#define mkInplaceDiv(cls) cls &operator/=(RT_FLOAT n) { m_data_ *= n; return *this; };
#endif //RAYTRACE_INCLUDE_IMPL_VECTOR_H_
