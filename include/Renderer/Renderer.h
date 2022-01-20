#ifndef RAYTRACE_INCLUDE_RENDERER_H_
#define RAYTRACE_INCLUDE_RENDERER_H_
#include "../Scene.h"
#include "../Canvas.h"
#include "../Camera/Camera.h"
namespace raytrace::renderer {

class RenderSet {
 public:
  RenderSet(const Scene &scene, const camera::Camera &camera) : r_camera_(camera), r_scene_(scene) {}
  const camera::Camera &GetCamera() const { return r_camera_; }
  const Scene &GetScene() const { return r_scene_; }
 private:
  const camera::Camera &r_camera_;
  const Scene &r_scene_;
};
class Renderer {
 public:
  virtual Canvas Render(const RenderSet &set) const = 0;
  virtual ~Renderer() {}
};
}

#endif //RAYTRACE_INCLUDE_RENDERER_H_
