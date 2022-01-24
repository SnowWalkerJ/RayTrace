#ifndef RAYTRACE_INCLUDE_MATERIAL_METAL_H_
#define RAYTRACE_INCLUDE_MATERIAL_METAL_H_
#include "Material.h"
namespace raytrace::material {
class Metal : public Material {
 public:
  bool Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const override;
};
}
#endif //RAYTRACE_INCLUDE_MATERIAL_METAL_H_
