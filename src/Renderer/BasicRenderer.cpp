#include <Renderer/BasicRenderer.h>
#include <impl/thread_pool.h>

namespace raytrace::renderer {
BasicRenderer::BasicRenderer(size_t width, size_t height, size_t samples_per_pixel, size_t max_scatter_times) {
  m_width_ = width;
  m_height_ = height;
  m_samples_per_pixel_ = samples_per_pixel;
  m_max_scatter_times_ = max_scatter_times;
}
Canvas BasicRenderer::Render(const RenderSet &set) const {
  Canvas canvas(m_width_, m_height_);
  thread_pool pool;
  pool.parallelize_loop(0, m_width_, [&](size_t start, size_t end) {
    for (size_t x = start; x < end; x++) {
      for (size_t y = 0; y < m_height_; y++) {
        Color color = Color::Black();
        for (size_t sample_idx = 0; sample_idx < m_samples_per_pixel_; sample_idx++) {
          color += Sample(x, y, set);
        }
        canvas.Pixel(x, y) = (color / m_samples_per_pixel_).Truncate();
      }
    }
  });
//  for (size_t x = 0; x < m_width_; x++) {
//    for (size_t y = 0; y < m_height_; y++) {
//      Color color = Color::Black();
//      for (size_t sample_idx = 0; sample_idx < m_samples_per_pixel_; sample_idx++) {
//        color += Sample(x, y, set);
//      }
//      canvas.Pixel(x, y) = (color / m_samples_per_pixel_).Truncate();
//    }
//  }
  return canvas;
}
Color BasicRenderer::Sample(size_t x, size_t y, const RenderSet &set) const {
  Rng &rng = GetRandomGenerator();
  RT_FLOAT x_center = static_cast<RT_FLOAT>(x) / m_width_;
  RT_FLOAT y_center = static_cast<RT_FLOAT>(y) / m_height_;
  RT_FLOAT x_sample = x_center + (rng.nextFloat() - 0.5) / m_width_;
  RT_FLOAT y_sample = y_center + (rng.nextFloat() - 0.5) / m_height_;
  Ray ray = set.GetCamera().MakeRay(x_sample, y_sample);
  Color color = Trace(set, ray, m_max_scatter_times_);
  return color;
}
Color BasicRenderer::Trace(const RenderSet &set, const Ray &ray, size_t remain_scatter_times) const {
  Intersection intersection;
  bool intersected = set.GetScene().Intersect(ray, intersection);
  if (intersected) {
    const material::Material *material = intersection.p_material_;
    Color ret = material->Emmit();
    if (remain_scatter_times > 0) {
      Ray rout;
      bool scattered = material->Scatter(intersection.m_normal_, ray.Calculate(intersection.m_t_), ray, rout);
      if (scattered) {
        Color light_color = Trace(set, rout, remain_scatter_times - 1);
        Color color = material->NoAbsorb();
        ret = ret + color * light_color;
      }
    }
    return ret;
  }
  return set.GetScene().GetBackground();
}
}