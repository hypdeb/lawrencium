#ifndef _LAWRENCIUM_CCPG_VECTORS_H_
#define _LAWRENCIUM_CCPG_VECTORS_H_

#include "shared.h"
#include <optional>
#include <vector>

namespace lawrencium {
namespace ccpg {
namespace library {

struct GpuVector {
  int length;
  float *elements;
};

std::optional<library::GpuOperationException>
AddVectors(const GpuVector lhs, const GpuVector rhs, GpuVector result);

} // namespace library
} // namespace ccpg
} // namespace lawrencium

#endif