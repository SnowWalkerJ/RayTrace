#ifndef RAYTRACE_INCLUDE_MATERIAL_LIGHT_H_
#define RAYTRACE_INCLUDE_MATERIAL_LIGHT_H_
#include "Material.h"
#include "../Rng.h"
namespace raytrace::material {
class Light : public Material {
 public:
  Light(const Color &color) : m_color_(color) {}
  Color NoAbsorb() const override { return Color::Black(); }
  Color Emmit() const override { return m_color_; }
  bool Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const override {
    return false;
  }
 private:
  Color m_color_;
};
}
#endif //RAYTRACE_INCLUDE_MATERIAL_LIGHT_H_
