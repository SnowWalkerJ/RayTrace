#ifndef RAYTRACE_INCLUDE_TEXTURE_IMAGE_H_
#define RAYTRACE_INCLUDE_TEXTURE_IMAGE_H_
#include "Texture.h"
#include <memory>
#include <string>
namespace raytrace::texture {
class Image : public Texture {
 public:
  Image(const std::string &filename);
  Color GetColor(RT_FLOAT u, RT_FLOAT v) const override;
 private:
  std::unique_ptr<unsigned char[]> p_data_;
  int m_width_, m_height_;
  int m_channels_;
};
}
#endif //RAYTRACE_INCLUDE_TEXTURE_IMAGE_H_
