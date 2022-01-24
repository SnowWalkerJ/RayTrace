#ifndef RAYTRACE_INCLUDE_OBJECT_H_
#define RAYTRACE_INCLUDE_OBJECT_H_
#include "Material/Material.h"
#include "Texture/Texture.h"
#include "Shape/Shape.h"
#include "Hittable.h"
namespace raytrace {
class AbstractObject : public Hittable {
 public:
  virtual const material::Material &GetMaterial() const = 0;
  virtual const texture::Texture &GetTexture() const = 0;
  virtual const Shape &GetShape() const = 0;
};
template <typename S, typename M, typename T>
class ConcreteObject : public AbstractObject {
 public:
  ConcreteObject(S shape, M material, T texture) : m_shape_(std::move(shape)), m_material_(std::move(material)), m_texture_(std::move(texture)) {}
  const Shape &GetShape() const override { return m_shape_; }
  const material::Material &GetMaterial() const override { return m_material_; }
  const texture::Texture &GetTexture() const override { return m_texture_; }
  bool Intersect(const Ray &ray, Intersection &intersection) const override {
    if (m_shape_.Intersect(ray, intersection)) {
      intersection.p_object_ = this;
      return true;
    }
    return false;
  }
 private:
  S m_shape_;
  M m_material_;
  T m_texture_;
};
}
#endif //RAYTRACE_INCLUDE_OBJECT_H_
