#ifndef RAYTRACE_INCLUDE_TEXTURE_CHECKER_H_
#define RAYTRACE_INCLUDE_TEXTURE_CHECKER_H_
#include "Texture.h"
namespace raytrace::texture {
class Checker : public Texture {
 public:
  Checker(Color c1, Color c2, RT_FLOAT freq) {
    m_freq_ = freq;
    m_c_[0] = c1;
    m_c_[1] = c2;
  }
  Color GetColor(RT_FLOAT u, RT_FLOAT v) const override {
    int a = static_cast<int>(u * m_freq_), b = static_cast<int>(v * m_freq_);
    int c = std::abs(a - b) % 2;
    return m_c_[c];
  }
 private:
  RT_FLOAT m_freq_;
  Color m_c_[2];
};
}
#endif //RAYTRACE_INCLUDE_TEXTURE_CHECKER_H_
