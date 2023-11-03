#include "utils.h"
#include <algorithm>
#include <iterator>
#include <random>
#include <vector>

namespace common = lawrencium::common;

std::vector<float> common::RandomVector(int length) {
  // First create an instance of an engine.
  std::random_device rnd_device;
  // Specify the engine and distribution.
  std::mt19937 mersenne_engine{rnd_device()};
  std::uniform_real_distribution<float> dist{-10, 10};

  auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };

  std::vector<float> vec(length);
  std::generate(std::begin(vec), std::end(vec), gen);
  return vec;
}