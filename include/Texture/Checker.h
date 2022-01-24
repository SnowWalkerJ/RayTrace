#ifndef RAYTRACE_INCLUDE_TEXTURE_CHECKER_H_
#define RAYTRACE_INCLUDE_TEXTURE_CHECKER_H_
#include "Texture.h"
namespace raytrace::texture {
class Checker : public Texture {
 public:
  Checker(Color c1, Color c2, RT_FLOAT width) {
    m_width_ = width;
    m_c_[0] = c1;
    m_c_[1] = c2;
  }
  Color GetColor(RT_FLOAT u, RT_FLOAT v) const override {
    int a = static_cast<int>(u * m_width_ / M_PI), b = static_cast<int>(v * m_width_ / M_PI);
    int c = (a + b) % 2;
    return m_c_[c];
  }
 private:
  RT_FLOAT m_width_;
  Color m_c_[2];
};
}
#endif //RAYTRACE_INCLUDE_TEXTURE_CHECKER_H_
