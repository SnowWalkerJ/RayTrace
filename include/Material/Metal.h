#ifndef RAYTRACE_INCLUDE_MATERIAL_METAL_H_
#define RAYTRACE_INCLUDE_MATERIAL_METAL_H_
#include "Material.h"
namespace raytrace::material {
class Metal : public Material {
 public:
  Metal(const Color &color) : m_color_(color) {}
  Color NoAbsorb() const override { return m_color_; }
  bool Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const override;
 private:
  Color m_color_;
};
}
#endif //RAYTRACE_INCLUDE_MATERIAL_METAL_H_
