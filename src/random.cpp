#include <Rng.h>
using namespace raytrace;
namespace raytrace {
Rng &GetRandomGenerator() {
  static Rng rng;
  return rng;
}
}