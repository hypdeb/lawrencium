#include "neural_nets/neural_nets.h"
#include <gtest/gtest.h>
#include <vector>

namespace nns = lawrencium::neural_nets;

TEST(TestLayerSequence, TestInstantiate) {
  const auto layer_sequence = nns::LayerSequence{
      .layers = std::vector<nns::Layer>{nns::FullyConnected{
          .weights = std::vector<float>{0.1, 0.2, 0.3},
          .biases = std::vector<float>{1.0, 2.0, 3.0},
      }}};
}