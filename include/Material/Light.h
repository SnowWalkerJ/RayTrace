#ifndef RAYTRACE_INCLUDE_MATERIAL_LIGHT_H_
#define RAYTRACE_INCLUDE_MATERIAL_LIGHT_H_
#include "Material.h"
#include "../Rng.h"
namespace raytrace::material {
class Light : public Material {
 public:
  explicit Light(const Color &color) : m_color_(color) {}
  bool Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const override {
    return false;
  }
  Color Emmit() const override { return m_color_; }
 private:
  Color m_color_;
};
}
#endif //RAYTRACE_INCLUDE_MATERIAL_LIGHT_H_
