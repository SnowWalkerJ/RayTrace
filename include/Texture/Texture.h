#ifndef RAYTRACE_INCLUDE_TEXTURE_TEXTURE_H_
#define RAYTRACE_INCLUDE_TEXTURE_TEXTURE_H_
#include "../Color.h"
namespace raytrace::texture {
class Texture {
 public:
  virtual ~Texture() = default;
  virtual Color GetColor(RT_FLOAT u, RT_FLOAT v) const = 0;
};
}
#endif //RAYTRACE_INCLUDE_TEXTURE_TEXTURE_H_
