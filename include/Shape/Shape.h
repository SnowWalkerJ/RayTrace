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
  Shape(material::Material *material) {
    p_material_ = material;
  }
  const material::Material *GetMaterial() const { return p_material_; }
 private:
  material::Material *p_material_;
};
}
#endif //RAYTRACE_INCLUDE_SHAPE_H_
