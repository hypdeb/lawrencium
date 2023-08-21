#ifndef _LAWRENCIUM_LEETCODE_LEETCODE_H_
#define _LAWRENCIUM_LEETCODE_LEETCODE_H_

#include "common/linked_list.h"
#include <concepts>
#include <string>
#include <vector>

namespace lawrencium {
namespace leetcode {

/**
 * Merges the two sorted parameter vectors into one sorted returned vector.
 *
 * @param nums1 The first sorted vector of length n.
 * @param nums2 The second sorted vector of length m.
 * @return A new sorted vector of length n + m.
 */
std::vector<int> MergeSortedArraysNaive(const std::vector<int> &nums1,
                                        const std::vector<int> &nums2);

/**
 * Reverses a linked list.
 *
 * @param linkedList The first node of the input linked list.
 * @return The first node of the reversed linked list.
 */
template <std::default_initializable T>
common::Node<T> *ReverseLinkedList(common::Node<T> *linkedList) {
  auto current = linkedList;
  auto next = current->next;
  current->next = nullptr;
  while (next) {
    auto tmpNext = next->next;
    next->next = current;
    current = next;
    next = tmpNext;
  }

  return current;
};

/**
 * Counts the balanced substrings in a string of zeroes an ones.
 *
 * @param str The input string.
 * @return The count of balanced substrings.
 */
int CountBinarySubstrings(const std::string &str);

/**
 * Calculates the length of the longest increasing path in a matrix.
 *
 * @param matrix The input matrix.
 * @return The length of the longest increasing path.
 */
int LongestIncreasingPathInMatrix(std::vector<std::vector<int>> &matrix);

} // namespace leetcode
} // namespace lawrencium

#endif