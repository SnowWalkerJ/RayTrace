#include <Texture/Image.h>
#include <impl/stb_image.h>

namespace raytrace::texture {
Image::Image(const std::string &filename) {
  p_data_.reset(stbi_load(filename.c_str(), &m_width_, &m_height_, &m_channels_, 3));
  if (!p_data_) {
    throw std::runtime_error("error loading image `" + filename + "`");
  }
}
Color Image::GetColor(RT_FLOAT u, RT_FLOAT v) const {
  int x = std::clamp<int>(static_cast<int>(u * m_width_), 0, m_width_ - 1),
      y = std::clamp<int>(static_cast<int>(v * m_height_), 0, m_height_ - 1);

  unsigned char *pixel = p_data_.get() + (y * m_width_ + x) * m_channels_;
  RT_FLOAT r = pixel[0] / 256.0,
           g = pixel[1] / 256.0,
           b = pixel[2] / 256.0;
  return {r, g, b};
}
}