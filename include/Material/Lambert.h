#ifndef RAYTRACE_INCLUDE_MATERIAL_LAMBERT_H_
#define RAYTRACE_INCLUDE_MATERIAL_LAMBERT_H_
#include "Material.h"
#include "../Rng.h"
namespace raytrace::material {
class LambertDiffuse : public Material {
 public:
  LambertDiffuse(const Color &color) : m_color_(color) {}
//  RT_FLOAT Pdf(const Vector &normal, const Point &point, const Ray &rayin, const Ray &rayout) const override {
//    RT_FLOAT cos = rayout.Direction().Normalize().dot()
//  }
  Color NoAbsorb() const override { return m_color_; }
//  Color Emmit() const override { return m_color_; }
  bool Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const override;
//  Color Emmit() const override { return m_color_ * 0.1; }
 private:
  Color m_color_;
};
}
#endif //RAYTRACE_INCLUDE_MATERIAL_LAMBERT_H_
