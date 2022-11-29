#ifndef RAYTRACE_INCLUDE_MATERIAL_MIXTURE_H_
#define RAYTRACE_INCLUDE_MATERIAL_MIXTURE_H_
#include <memory>
#include "Material.h"
#include <Rng.h>
namespace raytrace::material {
class Mixture : public Material {
 public:
  template <typename M1, typename M2>
  Mixture(RT_FLOAT ratio, M1 m1, M2 m2)
      : m_ratio_(ratio),
        m_material1_(std::make_unique<M1>(std::move(m1))),
        m_material2_(std::make_unique<M2>(std::move(m2))) {
  }
  bool Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const override {
    Rng &rng = GetRandomGenerator();
    if (rng.nextFloat() < m_ratio_) {
      return m_material1_->Scatter(normal, point, rin, rout);
    } else {
      return m_material2_->Scatter(normal, point, rin, rout);
    }
  }
 private:
  RT_FLOAT m_ratio_;
  std::unique_ptr<Material> m_material1_, m_material2_;
};
}
#endif //RAYTRACE_INCLUDE_MATERIAL_MIXTURE_H_
