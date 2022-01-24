#ifndef RAYTRACE_INCLUDE_MATERIAL_LAMBERT_H_
#define RAYTRACE_INCLUDE_MATERIAL_LAMBERT_H_
#include "Material.h"
#include "../Rng.h"
namespace raytrace::material {
class LambertDiffuse : public Material {
 public:
  bool Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const override;
};
}
#endif //RAYTRACE_INCLUDE_MATERIAL_LAMBERT_H_
