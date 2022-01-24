#ifndef RAYTRACE_INCLUDE_SHAPE_SPHERE_H_
#define RAYTRACE_INCLUDE_SHAPE_SPHERE_H_
#include "Shape.h"
#include <cmath>
namespace raytrace::shape {
class Sphere : public Shape {
 public:
  Sphere(Point position, RT_FLOAT radius) : Shape(), m_position_(position), m_radius_(radius) {}
  bool Intersect(const Ray &ray, Intersection &intersection) const override;
 protected:
  bool SetIntersection(const Ray &ray, RT_FLOAT t, Intersection &intersection) const;
 private:
  Point m_position_;
  RT_FLOAT m_radius_;
};
}
#endif //RAYTRACE_INCLUDE_SHAPE_SPHERE_H_
