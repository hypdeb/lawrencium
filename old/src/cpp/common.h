#ifndef _LAWRENCIUM_SRC_CPP_COMMON_H_
#define _LAWRENCIUM_SRC_CPP_COMMON_H_

#include <algorithm>
#include <concepts>
#include <ranges>
#include <vector>

namespace lawrencium {
namespace cpp {

template <typename T>
std::vector<T> DiagonalMatrixRawLoop(const int sideLength,
                                     const T diagonalValue)
  requires std::default_initializable<T>
{
  const auto numElements = sideLength * sideLength;
  auto result = std::vector<T>(numElements, T());
  for (auto i = 0; i < sideLength; ++i) {
    for (auto j = 0; j < sideLength; ++j) {
      result[i * sideLength + j] = i == j ? diagonalValue : T();
    }
  }
  return result;
};

} // namespace cpp
} // namespace lawrencium
#endif // _LAWRENCIUM_SRC_CPP_COMMON_H_