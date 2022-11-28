#ifndef RAYTRACE_INCLUDE_CAMERA_H_
#define RAYTRACE_INCLUDE_CAMERA_H_
#include <cmath>
#include "../Vector.h"
#include "../Ray.h"
#include "Camera.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
namespace raytrace::camera {
class PerspectiveCamera : public Camera {
 public:
  PerspectiveCamera(RT_FLOAT fieldOfViewInDegrees, RT_FLOAT aspect_ratio, const Point &origin, const Vector &target, const Vector &target_up) {
    m_fov_ = fieldOfViewInDegrees / 180 * M_PI;
    m_aspect_ratio_ = aspect_ratio;
    m_tan_fov_ = std::tan(m_fov_ / 2);
    m_origin_ = origin;
    m_forward_ = (target - origin).Normalize();
    m_right_ = m_forward_.cross(target_up).Normalize();
    m_up_ = m_right_.cross(m_forward_).Normalize();
  }
  [[nodiscard]] Ray MakeRay(RT_FLOAT x, RT_FLOAT y) const override {
    Vector direction = (m_forward_ + (x - 0.5) * m_tan_fov_ * m_aspect_ratio_ * m_right_ + (y - 0.5) * m_tan_fov_ * m_up_).Normalize();
    return {m_origin_, direction};
  }

 private:
  RT_FLOAT m_fov_;
  RT_FLOAT m_tan_fov_;
  RT_FLOAT m_aspect_ratio_;
  Point m_origin_;
  Vector m_forward_;
  Vector m_right_;
  Vector m_up_;
};
}
#endif //RAYTRACE_INCLUDE_CAMERA_H_
