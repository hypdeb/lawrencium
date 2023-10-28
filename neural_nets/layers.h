#ifndef _LAWRENCIUM_NEURALNETS_LAYERS_H_
#define _LAWRENCIUM_NEURALNETS_LAYERS_H_

#include <variant>
#include <vector>

namespace lawrencium {
namespace neural_nets {
struct FullyConnected {
  std::vector<float> weights;
  std::vector<float> biases;
};

typedef std::variant<FullyConnected> Layer;

} // namespace neural_nets
} // namespace lawrencium

#endif