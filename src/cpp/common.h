#ifndef _LAWRENCIUM_SRC_CPP_COMMON_H_
#define _LAWRENCIUM_SRC_CPP_COMMON_H_

#include <algorithm>
#include <concepts>
#include <ranges>
#include <vector>

namespace lawrencium {
namespace cpp {

template <typename T>
std::vector<T> DiagonalMatrix(const int sideLength, const T diagonalValue)
  requires std::default_initializable<T>
{
  auto countToSideLength = std::views::iota(0, sideLength);
  auto rowIndexes = countToSideLength
                    | std::views::transform([sideLength](const auto i) {
                        return std::views::repeat(i, sideLength);
                      })
                    | std::views::join;
  auto columnIndexes
      = std::views::repeat(countToSideLength, sideLength) | std::views::join;
  auto zippedIndexes = std::views::zip(rowIndexes, columnIndexes);
  return zippedIndexes
         | std::views::transform([diagonalValue](const auto &tuple) {
             return (std::get<0>(tuple) == std::get<1>(tuple)) ? diagonalValue
                                                               : T();
           })
         | std::ranges::to<std::vector<T>>();
}

template <typename T>
std::vector<T> DiagonalMatrixRawLoop(const int sideLength,
                                     const T diagonalValue)
  requires std::default_initializable<T>
{
  const auto numElements = diagonalValue * diagonalValue;
  auto result = std::vector<T>(numElements, T());
  for (auto i = 0; i < sideLength; ++i) {
    result[i * sideLength + i] = diagonalValue;
  }
  return result;
}

} // namespace cpp
} // namespace lawrencium
#endif // _LAWRENCIUM_SRC_CPP_COMMON_H_