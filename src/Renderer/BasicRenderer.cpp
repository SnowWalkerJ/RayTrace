#include <Renderer/BasicRenderer.h>
#include <Object.h>
#include <Rng.h>
#include <Texture/Texture.h>
#include <Material/Material.h>
#include <impl/thread_pool.h>

namespace raytrace::renderer {
BasicRenderer::BasicRenderer(size_t width, size_t height, size_t samples_per_pixel, RT_FLOAT min_decay) {
  m_width_ = width;
  m_height_ = height;
  m_samples_per_pixel_ = samples_per_pixel;
  m_min_decay_ = min_decay;
}
Canvas BasicRenderer::Render(const RenderSet &set) const {
  Canvas canvas(m_width_, m_height_);
  thread_pool pool;
  pool.parallelize_loop(0ul, m_width_, [&](size_t start, size_t end) {
    for (size_t x = start; x < end; x++) {
      for (size_t y = 0; y < m_height_; y++) {
        Color color = Color::Black();
        for (size_t sample_idx = 0; sample_idx < m_samples_per_pixel_; sample_idx++) {
          color += Sample(x, y, set);
        }
        canvas.Pixel(x, y) = color / m_samples_per_pixel_;
      }
    }
  });
  return canvas;
}
Color BasicRenderer::Sample(size_t x, size_t y, const RenderSet &set) const {
  Rng &rng = GetRandomGenerator();
  RT_FLOAT x_center = static_cast<RT_FLOAT>(x) / m_width_;
  RT_FLOAT y_center = static_cast<RT_FLOAT>(y) / m_height_;
  RT_FLOAT x_sample = x_center + (rng.nextFloat() - 0.5) / m_width_;
  RT_FLOAT y_sample = y_center + (rng.nextFloat() - 0.5) / m_height_;
  Ray ray = set.GetCamera().MakeRay(x_sample, y_sample);
  Color color = Trace(set, ray);
  return color;
}
Color BasicRenderer::Trace(const RenderSet &set, const Ray &ray, Color decay, Color base) const {
  Intersection intersection;
  bool intersected = set.GetScene().Intersect(ray, intersection);
  if (intersected) {
    RT_FLOAT u = intersection.m_u_,
             v = intersection.m_v_;
    const material::Material &material = intersection.p_object_->GetMaterial();
    const texture::Texture &texture = intersection.p_object_->GetTexture();
    Color ret = material.Emmit() * decay + base;
    Ray rout;
    bool scattered = material.Scatter(intersection.m_normal_, ray.Calculate(intersection.m_t_), ray, rout);
    if (scattered) {
      Color color = texture.GetColor(u, v) * decay;
      if (color.Luminance() > m_min_decay_) {
        return Trace(set, rout, color, ret);
      }
    }
    return ret;
  }
  return set.GetScene().GetBackground();
}
}