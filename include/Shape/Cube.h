#ifndef RAYTRACE_INCLUDE_SHAPE_CUBE_H_
#define RAYTRACE_INCLUDE_SHAPE_CUBE_H_
#include "Shape.h"
namespace raytrace::shape {
class Cube : public Shape {
 public:
  Cube(const Point &pos, const Vector &d1, const Vector &d2, RT_FLOAT s1, RT_FLOAT s2, RT_FLOAT s3);
  bool Intersect(const Ray &ray, Intersection &intersection) const override;
  std::shared_ptr<BVHLeaf> BVH(const AbstractObject *) const override;
 private:
  Point m_pos_;
  Vector m_d_[3];
  RT_FLOAT m_s_[3];
};
}
#endif //RAYTRACE_INCLUDE_SHAPE_CUBE_H_
