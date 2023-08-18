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

template <typename SizeT>
auto SquareRowIndexes(const int sideLength)
  requires std::unsigned_integral<SizeT>
{
  const auto countToSideLength = std::views::iota(0, sideLength);
  return countToSideLength | std::views::transform([sideLength](const auto i) {
           return std::views::repeat(i, sideLength);
         })
         | std::views::join;
};

template <typename SizeT>
auto SquareColumnIndexes(const int sideLength)
  requires std::unsigned_integral<SizeT>
{
  const auto countToSideLength = std::views::iota(0, sideLength);
  return std::views::repeat(countToSideLength, sideLength) | std::views::join;
};

template <typename SizeT>
auto SquareCoordinates(const int sideLength)
  requires std::unsigned_integral<SizeT>
{
  auto rowIndexes = SquareRowIndexes<SizeT>(sideLength);
  auto columnIndexes = SquareColumnIndexes<SizeT>(sideLength);
  return std::views::zip(rowIndexes, columnIndexes);
};

template <typename ValueT, typename SizeT>
std::vector<ValueT> DiagonalMatrix(const SizeT sideLength,
                                   const ValueT diagonalValue)
  requires std::default_initializable<ValueT> && std::unsigned_integral<SizeT>
{
  auto zippedIndexes = SquareCoordinates<SizeT>(sideLength);
  return zippedIndexes
         | std::views::transform([diagonalValue](const auto &tuple) {
             return (std::get<0>(tuple) == std::get<1>(tuple)) ? diagonalValue
                                                               : ValueT();
           })
         | std::ranges::to<std::vector<ValueT>>();
};

template <template <typename> typename RangeT, typename ValueT, typename SizeT>
std::vector<ValueT>
DiagonalMatrixFromValues(const SizeT sideLength,
                         const RangeT<ValueT> &diagonalValues)
  requires std::default_initializable<ValueT> && std::unsigned_integral<SizeT>
           && std::ranges::range<RangeT<ValueT>>
{
  auto zippedIndexes = SquareCoordinates<SizeT>(sideLength);
  auto alignedDiagonalValues
      = diagonalValues | std::views::repeat(diagonalValues, sideLength);
  return zippedIndexes | std::views::zip(zippedIndexes, alignedDiagonalValues)
         | std::views::transform([](const auto &tuple) {
             return (std::get<0>(std::get<0>(tuple))
                     == std::get<1>(std::get<0>(tuple)))
                        ? std::get<1>(tuple)
                        : ValueT();
           })
         | std::ranges::to<std::vector<ValueT>>();
};

} // namespace matrixes
} // namespace cpp
} // namespace lawrencium
#endif // _LAWRENCIUM_SRC_CPP_COMMON_H_