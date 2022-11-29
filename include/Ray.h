#ifndef RAYTRACE_INCLUDE_RAY_H_
#define RAYTRACE_INCLUDE_RAY_H_
#include "Vector.h"
#include <numeric>
namespace raytrace {
class Ray {
 public:
  Ray() = default;
  Ray(const Point &origin, const Vector &direction) {
    m_origin_ = origin;
    m_direction_ = direction;
  }
  Point Calculate(RT_FLOAT t) const {
    return Point(m_origin_ + t * m_direction_);
  }
  const Point &Origin() const { return m_origin_; }
  const Vector &Direction() const { return m_direction_; }
 private:
  Point m_origin_;
  Vector m_direction_;
};

class AbstractObject;

struct Intersection {
  Intersection() {
    m_t_ = std::numeric_limits<RT_FLOAT>::max();
    p_object_ = nullptr;
  }
  RT_FLOAT m_t_;                       // length of the ray from origin to intersection
  RT_FLOAT m_u_, m_v_;                 // 2D coordinate on surface
  Vector m_normal_;
  const AbstractObject *p_object_;
};
}
#endif //RAYTRACE_INCLUDE_RAY_H_
