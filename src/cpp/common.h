#ifndef _LAWRENCIUM_SRC_CPP_COMMON_H_
#define _LAWRENCIUM_SRC_CPP_COMMON_H_

#include <algorithm>
#include <ranges>
#include <vector>

namespace lawrencium {
namespace cpp {

template <typename T>
std::vector<T> DiagonalMatrix(const int sideLength, const T diagonalValue) {
  const auto numElements = sideLength * sideLength;
  const auto result = std::vector<T>(numElements);
  const auto rowIndexes =
      std::views::iota(1, 10) | std::views::transform([](const auto i) {
        return std::views::repeat(sideLength, i)
      });
  // return std::views::iota(1, 10) | std::views::transform([](const auto i)
  // {return });
  // TODO : actually implement, using views ideally.
  return result;
}

} // namespace cpp
} // namespace lawrencium
#endif // _LAWRENCIUM_SRC_CPP_COMMON_H_