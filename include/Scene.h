#ifndef RAYTRACE_INCLUDE_SCENE_H_
#define RAYTRACE_INCLUDE_SCENE_H_
#include <list>
#include <memory>
#include "Hittable.h"
#include "Color.h"
#include "Object.h"

namespace raytrace {
class Shape;

class Scene : public Hittable {
 public:
  Scene() = default;
  Scene(const Scene &) = delete;
  Scene(Scene &&) noexcept = default;
  Scene &operator=(const Scene &) = delete;
  Scene &operator=(Scene &&) noexcept = default;
  Scene &SetBackground(const Color &color) {
    m_background_ = color;
    return *this;
  }
  Color GetBackground() const { return m_background_; }
  template<typename...Args>
  Hittable *AddObject(Args &&...args) {
    using Object = ConcreteObject<Args...>;
    m_objects_.push_back(std::make_unique<Object>(std::forward<Args>(args)...));
    return m_objects_.back().get();
  }
  bool Intersect(const Ray &ray, Intersection &intersection) const override {
    bool intersected = false;
    for (auto &&obj : m_objects_) {
      intersected = obj->Intersect(ray, intersection) || intersected;
    }
    return intersected;
  }
 private:
  Color m_background_ = Color::Black();
  std::list<std::unique_ptr<AbstractObject>> m_objects_;
};

} // namespace raytrace
#endif //RAYTRACE_INCLUDE_SCENE_H_
