#ifndef RAYTRACE_INCLUDE_CAMERA_CAMERA_H_
#define RAYTRACE_INCLUDE_CAMERA_CAMERA_H_
#include "../Ray.h"
namespace raytrace {
namespace camera {
class Camera {
 public:
  virtual Ray MakeRay(RT_FLOAT u, RT_FLOAT v) const = 0;
  virtual ~Camera() {}
};
}
}
#endif //RAYTRACE_INCLUDE_CAMERA_CAMERA_H_
