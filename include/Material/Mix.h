#ifndef RAYTRACE_INCLUDE_MATERIAL_MIX_H_
#define RAYTRACE_INCLUDE_MATERIAL_MIX_H_
#include <memory>
#include "Material.h"
#include <Rng.h>
namespace raytrace::material {
template <typename M1, typename M2>
class MixMaterial : public Material {
 public:
  MixMaterial(RT_FLOAT ratio, M1 m1, M2 m2)
      : m_ratio_(ratio),
        m_material1_(std::move(m1)),
        m_material2_(std::move(m2)) {
  }
  bool Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const override {
    Rng &rng = GetRandomGenerator();
    if (rng.nextFloat() < m_ratio_) {
      return m_material1_.Scatter(normal, point, rin, rout);
    } else {
      return m_material2_.Scatter(normal, point, rin, rout);
    }
  }
 private:
  RT_FLOAT m_ratio_;
  M1 m_material1_;
  M2 m_material2_;
};
}
#endif //RAYTRACE_INCLUDE_MATERIAL_MIX_H_
