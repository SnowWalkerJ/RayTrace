#ifndef RAYTRACE_INCLUDE_CANVAS_H_
#define RAYTRACE_INCLUDE_CANVAS_H_
#include <stddef.h>
#include <memory>
#include "Color.h"
namespace raytrace {
class Canvas {
 public:
  Canvas(size_t width, size_t height) {
    m_width_ = width;
    m_height_ = height;
    m_data_ = std::make_unique<Color[]>(height * width);
  }
  Canvas(const Canvas &) = delete;
  Canvas(Canvas &&) noexcept = default;
  Canvas &operator=(const Canvas &) = delete;
  Canvas &operator=(Canvas &&) noexcept = default;
  Color &Pixel(size_t x, size_t y)  noexcept{
    return m_data_[x + y * m_width_];
  }
  const Color &Pixel(size_t x, size_t y) const noexcept {
    return m_data_[x + y * m_width_];
  }
  Color &PixelSafe(size_t x, size_t y) {
    assert(x >= 0 && x < m_width_ && y >= 0 && y < m_height_ && "index out of range");
    return m_data_[x + y * m_width_];
  }
  const Color &PixelSafe(size_t x, size_t y) const {
    assert(x >= 0 && x < m_width_ && y >= 0 && y < m_height_ && "index out of range");
    return m_data_[x + y * m_width_];
  }
  size_t Width() const noexcept { return m_width_; }
  size_t Height() const noexcept { return m_height_; }
 private:
  size_t m_width_, m_height_;
  std::unique_ptr<Color[]> m_data_;
};
} // namepsace raytrace
#endif //RAYTRACE_INCLUDE_CANVAS_H_
