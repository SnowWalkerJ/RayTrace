#ifndef RAYTRACE_INCLUDE_MATERIAL_MATERIAL_H_
#define RAYTRACE_INCLUDE_MATERIAL_MATERIAL_H_
#include "../Vector.h"
#include "../Ray.h"
#include "../Color.h"
namespace raytrace::material {
class Material {
 public:
  virtual bool Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const = 0;
  virtual Color Emmit() const { return Color::Black(); }
  virtual ~Material() = default;
};
}
#endif //RAYTRACE_INCLUDE_MATERIAL_MATERIAL_H_
