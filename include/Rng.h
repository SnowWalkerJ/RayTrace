#ifndef RAYTRACE_INCLUDE_RNG_H_
#define RAYTRACE_INCLUDE_RNG_H_
#include <stdint.h>
namespace raytrace {
class Rng {
 public:
  Rng(uint32_t z = 362436069, uint32_t w = 521288629) : m_z(z), m_w(w) {}
  // Returns a 'canonical' float from [0,1)
  float nextFloat() noexcept {
    uint32_t i = nextUInt32();
    return i * 2.328306e-10f;
  }

  // Returns an int with random bits set
  uint32_t nextUInt32() noexcept {
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
  }
 private:
  uint32_t m_z, m_w;
};

Rng &GetRandomGenerator();
}
#endif //RAYTRACE_INCLUDE_RNG_H_
