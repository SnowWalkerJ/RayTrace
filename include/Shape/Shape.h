#ifndef RAYTRACE_INCLUDE_SHAPE_H_
#define RAYTRACE_INCLUDE_SHAPE_H_
#include "../Vector.h"
#include "../Color.h"
#include "../Hittable.h"
#include "../Material/Material.h"

namespace raytrace {
class Intersection;

class Shape : public Hittable {
 public:
  Shape() = default;
};
}
#endif //RAYTRACE_INCLUDE_SHAPE_H_
