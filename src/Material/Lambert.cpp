#include <Material/Lambert.h>

namespace raytrace::material {
bool LambertDiffuse::Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const {
  Point sphere_center = point + normal;
  Rng &rng = GetRandomGenerator();
  Vector sample_v;
  do {
    sample_v = Vector(
        rng.nextFloat() * 2 - 1,
        rng.nextFloat() * 2 - 1,
        rng.nextFloat() * 2 - 1
        );
  } while (sample_v.Norm() > 1);
  Vector out_direction = (sample_v.Normalize() + sphere_center - point).Normalize();
  rout = Ray(point, out_direction);
  return true;
}
}