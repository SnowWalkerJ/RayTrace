#include <Shape/Cube.h>
namespace raytrace::shape {
Cube::Cube(const Point &pos, const Vector &d1, const Vector &d2, RT_FLOAT s1, RT_FLOAT s2, RT_FLOAT s3, material::Material *material1) : Shape(material1) {
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
  for (int d = 0; d < 3; d++) {
    const Vector vd[] = {m_d_[d], -m_d_[d]};
    for (int i = 0; i < 2; i++) {
      const Point p1 = m_pos_ + m_s_[d] / 2 * vd[i];
      RT_FLOAT solution = (p1 - ray.Origin()).dot(vd[i]) / ray.Direction().dot(vd[i]);
      const Vector &v1 = m_d_[(d + 1) % 3],
                   &v2 = m_d_[(d + 2) % 3];
      auto [c1, c2] = (ray.Calculate(solution) - p1).Decompose(v1, v2);
      const RT_FLOAT s1 = m_s_[(d + 1) % 3] / 2,
                     s2 = m_s_[(d + 2) % 3] / 2;
//      std::cout << c1 << ',' << c2 << std::endl;
      if (solution > kRT_MIN_T && solution < intersection.m_t_ && std::fabs(c1) < s1 && std::fabs(c2) < s2) {
        SetIntersection(intersection, vd[i], solution);
        intersected = true;
      }
    }
  }
  return intersected;
}
void Cube::SetIntersection(Intersection &intersection, const Vector &vd, RT_FLOAT t) const {
  intersection.p_object_ = this;
  intersection.m_t_ = t;
  intersection.m_normal_ = vd;
  intersection.p_material_ = GetMaterial();
}
}