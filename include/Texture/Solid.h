#ifndef RAYTRACE_INCLUDE_TEXTURE_SOLID_H_
#define RAYTRACE_INCLUDE_TEXTURE_SOLID_H_
#include "Texture.h"
namespace raytrace::texture {
class Solid : public Texture {
 public:
  Solid(const Color &color) : m_color_(color) {}
  Color GetColor(RT_FLOAT u, RT_FLOAT v) const { return m_color_; }
 private:
  Color m_color_;
};
}
#endif //RAYTRACE_INCLUDE_TEXTURE_SOLID_H_
