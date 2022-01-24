#ifndef RAYTRACE_INCLUDE_MATERIAL_DIELECTRIC_H_
#define RAYTRACE_INCLUDE_MATERIAL_DIELECTRIC_H_
#include "Material.h"
namespace raytrace::material {
class Dielectric : public Material {
 public:
  Dielectric(RT_FLOAT refraction);
  bool Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const override;
 private:
  RT_FLOAT m_refraction_;
};
}
#endif //RAYTRACE_INCLUDE_MATERIAL_DIELECTRIC_H_
