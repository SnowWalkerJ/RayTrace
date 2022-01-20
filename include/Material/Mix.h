#ifndef RAYTRACE_INCLUDE_MATERIAL_MIX_H_
#define RAYTRACE_INCLUDE_MATERIAL_MIX_H_
#include <memory>
#include "Material.h"
#include <Rng.h>
namespace raytrace::material {
template <typename M1, typename M2>
class MixMaterial : public Material {
 public:
  MixMaterial(RT_FLOAT ratio) {
    m_ratio_ = ratio;
  }
  template<typename...Args>
  void SetMaterial1(Args&&...args) {
    m_material1_ = std::make_unique<M1>(std::forward<Args>(args)...);
  }
  template<typename...Args>
  void SetMaterial2(Args&&...args) {
    m_material2_ = std::make_unique<M1>(std::forward<Args>(args)...);
  }
  bool IsLight() const override { return m_material1_->IsLight() || m_material2_->IsLight(); }
  Color Emmit() const override { return m_material1_->Emmit() * m_ratio_ + m_material2_->Emmit() * (1 - m_ratio_); }
  Color NoAbsorb() const override { return m_material1_->NoAbsorb() * m_ratio_ + m_material2_->NoAbsorb() * (1 - m_ratio_); }
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
  std::unique_ptr<M1> m_material1_;
  std::unique_ptr<M2> m_material2_;
};
}
#endif //RAYTRACE_INCLUDE_MATERIAL_MIX_H_
