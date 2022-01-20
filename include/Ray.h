#ifndef RAYTRACE_INCLUDE_RAY_H_
#define RAYTRACE_INCLUDE_RAY_H_
#include "Vector.h"
#include <numeric>
namespace raytrace {
class Ray {
 public:
  constexpr Ray() = default;
  constexpr Ray(const Point &origin, const Vector &direction) {
    m_origin_ = origin;
    m_direction_ = direction;
  }
  Point Calculate(RT_FLOAT t) const {
    return m_origin_ + t * m_direction_;
  }
  const Point &Origin() const { return m_origin_; }
  const Vector &Direction() const { return m_direction_; }
 private:
  Point m_origin_;
  Vector m_direction_;
};

class Hittable;
namespace material {
class Material;
}

struct Intersection {
  Intersection() {
    m_t_ = std::numeric_limits<RT_FLOAT>::max();
    p_object_ = nullptr;
    p_material_ = nullptr;
  }
  RT_FLOAT m_t_;                       // length of the ray from origin to intersection
  RT_FLOAT m_u_, m_v_;                 // 2D coordinate on surface
  Vector m_normal_;
  const Hittable *p_object_;
  const material::Material *p_material_;
};
}
#endif //RAYTRACE_INCLUDE_RAY_H_
