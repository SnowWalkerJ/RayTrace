#ifndef RAYTRACE_INCLUDE_SHAPE_H_
#define RAYTRACE_INCLUDE_SHAPE_H_
#include <memory>
#include "../Vector.h"
#include "../Color.h"
#include "../Hittable.h"
#include "../Material/Material.h"

namespace raytrace {
class Intersection;
class AbstractObject;
class BVHLeaf;

class Shape : public Hittable {
 public:
  Shape() = default;
  [[nodiscard]] virtual std::shared_ptr<BVHLeaf> BVH(const AbstractObject *) const = 0;
};
}
#endif //RAYTRACE_INCLUDE_SHAPE_H_
