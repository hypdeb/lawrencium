#ifndef _LAWRENCIUM_LEETCODE_LEETCODE_H_
#define _LAWRENCIUM_LEETCODE_LEETCODE_H_

#include <span>
#include <vector>

namespace lawrencium {
namespace ita {

template <typename TValue> int random_partition(std::span<TValue> input) {
  auto i = 0;
  auto j = 0;
  const auto &pivot_value = input[input.size() - 1];
  while (j < input.size() - 1) {
    const auto &new_value = input[j];
    if (new_value > pivot_value) {
      // Do not do anything, just move j.
    } else {
      const auto swap = input[i];
      input[i] = new_value;
      input[j] = swap;
      i++;
    }
    j++;
  }
  return i;
};

template <typename TValue> void quick_sort(std::span<TValue> input) {
  if (input.size() <= 1) {
    return;
  }
  const auto i = random_partition(input);
  quick_sort(input.subspan(0, i));
  quick_sort(input.subspan(i, input.size()));
};
} // namespace ita
} // namespace lawrencium
#endif