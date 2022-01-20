#include <Material/Metal.h>

namespace raytrace::material {
bool Metal::Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const {
  Vector vin = rin.Direction();
  RT_FLOAT cos = vin.dot(normal);
  Vector vout = vin - normal * (cos * 2);
  assert(abs(vout.Norm() - 1) < 1e-5);
  rout = Ray(point, vout);
  return true;
}
}