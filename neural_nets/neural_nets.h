#ifndef _LAWRENCIUM_NEURALNETS_NEURALNETS_H_
#define _LAWRENCIUM_NEURALNETS_NEURALNETS_H_

#include "layers.h"
#include <vector>

namespace lawrencium {
namespace neural_nets {
struct LayerSequence {
  std::vector<Layer> layers;
};
} // namespace neural_nets
} // namespace lawrencium

#endif