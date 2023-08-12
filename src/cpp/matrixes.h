#ifndef _LAWRENCIUM_SRC_CPP_MATRIXES_H_
#define _LAWRENCIUM_SRC_CPP_MATRIXES_H_

#include <algorithm>
#include <concepts>
#include <ranges>
#include <tuple>
#include <vector>

namespace lawrencium {
namespace cpp {
namespace matrixes {

std::ranges::view<int> RowIndexes(const int sideLength);

std::ranges::view<int> ColumnIndexes(const int sideLength);

std::ranges::view<std::tuple<int, int>> Coordinates(const int sideLength);

template <typename T>
std::vector<T> DiagonalMatrix(const int sideLength, const T diagonalValue)
  requires std::default_initializable<T>
{
  auto zippedIndexes = Coordinates(sideLength);
  return zippedIndexes
         | std::views::transform([diagonalValue](const auto &tuple) {
             return (std::get<0>(tuple) == std::get<1>(tuple)) ? diagonalValue
                                                               : T();
           })
         | std::ranges::to<std::vector<T>>();
};

} // namespace matrixes
} // namespace cpp
} // namespace lawrencium
#endif // _LAWRENCIUM_SRC_CPP_COMMON_H_