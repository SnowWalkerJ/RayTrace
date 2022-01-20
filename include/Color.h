#ifndef RAYTRACE_INCLUDE_COLOR_H_
#define RAYTRACE_INCLUDE_COLOR_H_
#include "impl/vector.h"
#include <algorithm>
namespace raytrace {
class Color {
 public:
  constexpr Color() : Color(0.0, 0.0, 0.0) {}
  constexpr Color(RT_FLOAT r, RT_FLOAT g, RT_FLOAT b) : m_data_(r, g, b) {}
  Color(const Color &) noexcept = default;
  Color &operator=(const Color &) noexcept = default;
  RT_FLOAT R() const { return m_data_.m_x; }
  RT_FLOAT G() const { return m_data_.m_y; }
  RT_FLOAT B() const { return m_data_.m_z; }
  Color Truncate(RT_FLOAT min=0.0f, RT_FLOAT max=1.0f) const {
    return Color(
        std::clamp(m_data_.m_x, min, max),
        std::clamp(m_data_.m_y, min, max),
        std::clamp(m_data_.m_z, min, max)
        );
  }
  static constexpr Color Black() { return {0, 0, 0}; }
  static constexpr Color Red() { return {1, 0, 0}; }
  static constexpr Color Green() { return {0, 1, 0}; }
  static constexpr Color Blue() { return {0, 0, 1}; }
  static constexpr Color White() { return {1, 1, 1}; }
  friend Color operator *(const Color &c1, const Color &c2) {
    return {
        c1.R() * c2.R(),
        c1.G() * c2.G(),
        c1.B() * c2.B()
        };
  }
  mkInplaceAdd(Color)
  mkInplaceSub(Color)
  mkInplaceMul(Color)
  mkInplaceDiv(Color)
  mkAdd(Color)
  mkSub(Color)
  mkMul(Color)
  mkDiv(Color)
 protected:
  explicit Color(const detail::vector3d &v) : m_data_(v) {}
 private:
  detail::vector3d m_data_;
};


} // namespace raytrace
#endif //RAYTRACE_INCLUDE_COLOR_H_
