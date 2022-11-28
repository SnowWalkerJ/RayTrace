#ifndef RAYTRACE_INCLUDE_RENDERER_BASICRENDERER_H_
#define RAYTRACE_INCLUDE_RENDERER_BASICRENDERER_H_
#include "Renderer.h"
namespace raytrace::renderer {
class BasicRenderer : public Renderer {
 public:
  BasicRenderer(size_t width, size_t height, size_t samples_per_pixel, RT_FLOAT min_decay);
  Canvas Render(const RenderSet &set) const override;
 protected:
  Color Sample(size_t x, size_t y, const RenderSet &set) const;
  Color Trace(const RenderSet &set, const Ray &ray, Color decay=Color(1, 1, 1), Color base=Color(0, 0, 0)) const;
 private:
  size_t m_width_;
  size_t m_height_;
  size_t m_samples_per_pixel_;
  RT_FLOAT m_min_decay_;
};
}

#endif //RAYTRACE_INCLUDE_RENDERER_BASICRENDERER_H_
