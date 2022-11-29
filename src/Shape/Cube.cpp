#include <Shape/Cube.h>
#include <BVH.h>
#include <Object.h>
namespace raytrace::shape {

static constexpr struct { RT_FLOAT su, sv, eu, ev; bool exchange; } uv_mapping[6] = {
    {0, 1.0 / 3, 0.25, 2.0 / 3, false},
    {0.75, 1.0 / 3, 0.5, 2.0 / 3, false},
    {0.5, 1.0 / 3, 0.25, 2.0 / 3, true},
    {0.75, 1.0 / 3, 1, 2.0 / 3, true},
    {0.5, 1.0, 0.25, 2.0 / 3, false},
    {0.5, 0, 0.25, 1.0 / 3, false}
};

Cube::Cube(const Point &pos, const Vector &d1, const Vector &d2, RT_FLOAT s1, RT_FLOAT s2, RT_FLOAT s3) : Shape() {
  m_pos_ = pos;
  m_d_[0] = d1;
  m_d_[1] = d2;
  m_d_[2] = cross(d1, d2).normalized();
  m_s_[0] = s1;
  m_s_[1] = s2;
  m_s_[2] = s3;
}
bool Cube::Intersect(const Ray &ray, Intersection &intersection) const {
  bool intersected = false;
  for (int d = 0; d < 3; d++) {
    auto against = m_d_[d].dot(ray.Direction()) < 0;
    auto v = (against * 2 - 1) * m_d_[d];
    int face = d * 2 + 1 - against;

    const Point p1 = m_pos_ + m_s_[d] / 2 * v;
    RT_FLOAT solution = (p1 - ray.Origin()).dot(v) / ray.Direction().dot(v);
    const Vector &v1 = m_d_[(d + 1) % 3],
        &v2 = m_d_[(d + 2) % 3];
    auto [c1, c2] = decompose(ray.Calculate(solution) - p1, v1, v2);
    const RT_FLOAT s1 = m_s_[(d + 1) % 3],
        s2 = m_s_[(d + 2) % 3];
    if (solution > kRT_MIN_T && solution < intersection.m_t_ && std::fabs(c1) < s1 / 2 && std::fabs(c2) < s2 / 2) {
      intersection.m_t_ = solution;
      intersection.m_normal_ = v;
      RT_FLOAT xu = c1 / s1 / 2 + 0.5, xv = c2 / s2 / 2 + 0.5;
      auto &m = uv_mapping[face];
      if (m.exchange) {
        std::swap(xu, xv);
      }
      intersection.m_u_ = m.su + xu * (m.eu - m.su);
      intersection.m_v_ = m.sv + xv * (m.ev - m.sv);
      intersected = true;
    }
  }
  return intersected;
}

std::shared_ptr<BVHLeaf> Cube::BVH(const AbstractObject *obj) const {
  Point vertex[] = {
      m_pos_ + m_d_[0] * m_s_[0] + m_d_[1] * m_s_[1] + m_d_[2] * m_s_[2],
      m_pos_ + m_d_[0] * m_s_[0] + m_d_[1] * m_s_[1] - m_d_[2] * m_s_[2],
      m_pos_ + m_d_[0] * m_s_[0] - m_d_[1] * m_s_[1] + m_d_[2] * m_s_[2],
      m_pos_ + m_d_[0] * m_s_[0] - m_d_[1] * m_s_[1] - m_d_[2] * m_s_[2],
      m_pos_ - m_d_[0] * m_s_[0] + m_d_[1] * m_s_[1] + m_d_[2] * m_s_[2],
      m_pos_ - m_d_[0] * m_s_[0] + m_d_[1] * m_s_[1] - m_d_[2] * m_s_[2],
      m_pos_ - m_d_[0] * m_s_[0] - m_d_[1] * m_s_[1] + m_d_[2] * m_s_[2],
      m_pos_ - m_d_[0] * m_s_[0] - m_d_[1] * m_s_[1] - m_d_[2] * m_s_[2]};
  return std::make_shared<BVHLeaf>(
      std::min({vertex[0].x(), vertex[1].x(), vertex[2].x(), vertex[3].x(), vertex[4].x(), vertex[5].x(), vertex[6].x(), vertex[7].x()}),
      std::max({vertex[0].x(), vertex[1].x(), vertex[2].x(), vertex[3].x(), vertex[4].x(), vertex[5].x(), vertex[6].x(), vertex[7].x()}),
      std::min({vertex[0].y(), vertex[1].y(), vertex[2].y(), vertex[3].y(), vertex[4].y(), vertex[5].y(), vertex[6].y(), vertex[7].y()}),
      std::max({vertex[0].y(), vertex[1].y(), vertex[2].y(), vertex[3].y(), vertex[4].y(), vertex[5].y(), vertex[6].y(), vertex[7].y()}),
      std::min({vertex[0].z(), vertex[1].z(), vertex[2].z(), vertex[3].z(), vertex[4].z(), vertex[5].z(), vertex[6].z(), vertex[7].z()}),
      std::max({vertex[0].z(), vertex[1].z(), vertex[2].z(), vertex[3].z(), vertex[4].z(), vertex[5].z(), vertex[6].z(), vertex[7].z()}),
      obj
      );
}
}