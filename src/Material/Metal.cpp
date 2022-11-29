#include <Material/Metal.h>

namespace raytrace::material {
bool Metal::Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const {
  const auto &vin = rin.Direction();
  RT_FLOAT cos = vin.dot(normal);
  auto vout = vin - normal * (cos * 2);
  assert(abs(vout.squaredNorm() - 1) < 1e-5);
  rout = Ray(point, vout);
  return true;
}
}