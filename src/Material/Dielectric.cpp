#include <Material/Dielectric.h>
#include <Rng.h>
#include <cmath>

namespace raytrace::material {
static RT_FLOAT reflectance(RT_FLOAT cosine, RT_FLOAT ref_idx) {
  // Use Schlick's approximation for reflectance.
  auto r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * std::pow((1 - cosine),5);
}

Dielectric::Dielectric(RT_FLOAT refraction) {
  m_refraction_ = refraction;
}

bool Dielectric::Scatter(const Vector &normal, const Point &point, const Ray &rin, Ray &rout) const {
  Vector vin = rin.Direction();
  RT_FLOAT cos = vin.dot(normal);
  RT_FLOAT sin = std::sqrt(1 - cos * cos);
  RT_FLOAT ratio;
  RT_FLOAT sign;
  if (cos < 0) {
    // ray from outside
    ratio = 1 / m_refraction_;
    sign = 1;
  } else {
    // ray from inside
    ratio = m_refraction_;
    sign = -1;
  }
  Rng &rng = GetRandomGenerator();
  Vector vout;
  if (ratio * sin <= 1 && reflectance(cos, m_refraction_) < rng.nextFloat()) {
    Vector vout_perp = ratio * (vin + sign * cos * normal);
    Vector vout_parallel = -sin * sign * normal;
    vout = (vout_perp + vout_parallel).Normalize();
    assert(abs(vout.Norm() - 1) < 1e-5);
  } else {
    vout = vin - normal * (cos * 2);
    if (abs(vout.Norm() - 1) >= 1e-5) {
      std::cout << cos << " " << vin << " " << normal << vout << std::endl;
      std::cout << vout.Norm() << std::endl;
      assert(abs(vout.Norm() - 1) < 1e-5);
    }
  }

  rout = Ray(point, vout);
  return true;
}
}