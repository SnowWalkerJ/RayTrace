#include <Shape/Cube.h>
namespace raytrace::shape {

static constexpr struct {RT_FLOAT su, sv, eu, ev; bool exchange;} uv_mapping[6] = {
  {0, 1.0/3, 0.25, 2.0/3, false},
  {0.75, 1.0/3, 0.5, 2.0/3, false},
  {0.5, 1.0/3, 0.25, 2.0/3, true},
  {0.75, 1.0/3, 1, 2.0/3, true},
  {0.5, 1.0, 0.25, 2.0/3, false},
  {0.5, 0, 0.25, 1.0/3, false}
};

Cube::Cube(const Point &pos, const Vector &d1, const Vector &d2, RT_FLOAT s1, RT_FLOAT s2, RT_FLOAT s3) : Shape() {
  m_pos_ = pos;
  m_d_[0] = d1;
  m_d_[1] = d2;
  m_d_[2] = d1.cross(d2).Normalize();
  m_s_[0] = s1;
  m_s_[1] = s2;
  m_s_[2] = s3;
}
bool Cube::Intersect(const Ray &ray, Intersection &intersection) const {
  bool intersected = false;
  int face = 0;
  for (int d = 0; d < 3; d++) {
    const Vector vd[] = {m_d_[d], -m_d_[d]};
    for (const auto & v : vd) {
      const Point p1 = m_pos_ + m_s_[d] / 2 * v;
      RT_FLOAT solution = (p1 - ray.Origin()).dot(v) / ray.Direction().dot(v);
      const Vector &v1 = m_d_[(d + 1) % 3],
                   &v2 = m_d_[(d + 2) % 3];
      auto [c1, c2] = (ray.Calculate(solution) - p1).Decompose(v1, v2);
      const RT_FLOAT s1 = m_s_[(d + 1) % 3],
                     s2 = m_s_[(d + 2) % 3];
      if (solution > kRT_MIN_T && solution < intersection.m_t_ && std::fabs(c1) < s1 / 2 && std::fabs(c2) < s2 / 2) {
        intersection.m_t_ = solution;
        intersection.m_normal_ = v;
        RT_FLOAT xu = c1 / s1 + 0.5, xv = c2 / s2 + 0.5;
        auto &m = uv_mapping[face];
        if (m.exchange) {
          std::swap(xu, xv);
        }
        intersection.m_u_ = m.su + xu / (m.eu - m.su);
        intersection.m_v_ = m.sv + xv / (m.ev - m.sv);
        intersected = true;
      }
      face++;
    }
  }
  return intersected;
}
}