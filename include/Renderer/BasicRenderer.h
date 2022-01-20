#ifndef RAYTRACE_INCLUDE_RENDERER_BASICRENDERER_H_
#define RAYTRACE_INCLUDE_RENDERER_BASICRENDERER_H_
#include "Renderer.h"
#include "../Rng.h"
#include "../Material/Material.h"
namespace raytrace {
namespace renderer {
class BasicRenderer : public Renderer {
 public:
  BasicRenderer(size_t width, size_t height, size_t samples_per_pixel, size_t max_scatter_times);
  Canvas Render(const RenderSet &set) const override;
 protected:
  Color Sample(size_t x, size_t y, const RenderSet &set) const;
  Color Trace(const RenderSet &set, const Ray &ray, size_t remain_scatter_times) const;
 private:
  size_t m_width_;
  size_t m_height_;
  size_t m_samples_per_pixel_;
  size_t m_max_scatter_times_;
};
}
}

#endif //RAYTRACE_INCLUDE_RENDERER_BASICRENDERER_H_
