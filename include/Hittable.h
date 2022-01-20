#ifndef RAYTRACE_INCLUDE_HITTABLE_H_
#define RAYTRACE_INCLUDE_HITTABLE_H_
#include "Ray.h"
namespace raytrace {
class Hittable {
 public:
  virtual bool Intersect(const Ray &ray, Intersection &) const = 0;
  virtual ~Hittable() {}
};
}
#endif //RAYTRACE_INCLUDE_HITTABLE_H_
