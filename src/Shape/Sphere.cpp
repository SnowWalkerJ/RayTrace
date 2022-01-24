#include <Shape/Sphere.h>
namespace raytrace::shape {
bool Sphere::Intersect(const Ray &ray, Intersection &intersection) const {
  // (p0 + t * d - c0) * (p0 + t * d - c0) = R^2
  // (p0 - c0) ^2 + t ^2 * d ^ 2 - 2 * d * t * (p0-c0) - R2 = 0
  const RT_FLOAT a = 1.0;
  const RT_FLOAT b = 2 * ray.Direction().dot(ray.Origin() - m_position_);
  const RT_FLOAT c = (ray.Origin() - m_position_).Norm2() - m_radius_ * m_radius_;
  const RT_FLOAT delta = b * b - 4 * a * c;
  if (delta < 0) {
    return false;
  } else if (delta == 0) {
    const RT_FLOAT solution = -b / 2 / a;
    return SetIntersection(ray, solution, intersection);;
  } else {
    const RT_FLOAT d = std::sqrt(delta);
    RT_FLOAT solution1 = (+d - b) / 2 / a,
             solution2 = (-d - b) / 2 / a;
    if (solution1 > solution2) {
      std::swap(solution1, solution2);
    }
    return SetIntersection(ray, solution1, intersection) || SetIntersection(ray, solution2, intersection);
  }
}
bool Sphere::SetIntersection(const Ray &ray, RT_FLOAT t, Intersection &intersection) const {
  if (t > 0 && t < intersection.m_t_) {
    intersection.m_normal_ = (ray.Calculate(t) - m_position_).Normalize();
    intersection.m_t_ = t;
    const Vector &n = intersection.m_normal_;
    RT_FLOAT phi = std::atan2(-n.Z(), n.X()) + M_PI,
             theta = std::acos(-n.Y());
    RT_FLOAT u = phi / 2 / M_PI,
             v = theta / M_PI;
    intersection.m_u_ = u;
    intersection.m_v_ = v;
    return true;
  } else {
    return false;
  }
}
}