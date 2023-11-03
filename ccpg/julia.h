#ifndef _LAWRENCIUM_CCPG_JULIA_H_
#define _LAWRENCIUM_CCPG_JULIA_H_

#include <vector>

namespace lawrencium {
namespace ccpg {
namespace julia {

struct cuComplex {
  float r;
  float i;

  float magnitude2() const;

  cuComplex operator*(const cuComplex &a) const;

  cuComplex operator+(const cuComplex &a) const;
};

std::vector<unsigned char> DrawOnGpu(const int image_dimension);

} // namespace julia
} // namespace ccpg
} // namespace lawrencium

#endif