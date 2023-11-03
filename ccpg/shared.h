#ifndef _LAWRENCIUM_CCPG_SHARED_H_
#define _LAWRENCIUM_CCPG_SHARED_H_

#include <string>

namespace lawrencium {
namespace ccpg {
namespace library {
struct GpuOperationException {
  std::string errorMessage;
};
} // namespace library
} // namespace ccpg
} // namespace lawrencium
#endif