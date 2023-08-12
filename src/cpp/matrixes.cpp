#include "matrixes.h"
#include <ranges>
#include <tuple>

namespace matrixes = lawrencium::cpp::matrixes;

std::ranges::view<int> matrixes::RowIndexes(const int sideLength) {
  auto countToSideLength = std::views::iota(0, sideLength);
  return = countToSideLength
           | std::views::transform([sideLength](const auto i) {
               return std::views::repeat(i, sideLength);
             })
           | std::views::join;
}

std::ranges::view<int> matrixes::RowIndexes(const int sideLength) {
  auto countToSideLength = std::views::iota(0, sideLength);
  return std::views::repeat(countToSideLength, sideLength) | std::views::join;
}

std::ranges::view<std::tuple<int, int>>
matrixes::Coordinates(const int sideLength) {
  auto rowIndexes = RowIndexes(sideLength);
  auto columnIndexes = ColumnIndexes(sideLength);
  return std::views::zip(rowIndexes, columnIndexes);
}