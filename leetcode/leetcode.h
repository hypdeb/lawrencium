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
 * @param nums1 The first sorted vector of length m.
 * @param m The length of the elements to sort in num1.
 * @param nums2 The second sorted vector of length n.
 * @param n The length of nums2.
 * @return Nothing, elements are sorted in nums1.
 */
void MergeSortedArraysNaive(std::vector<int> *nums1,
                            const int m,
                            const std::vector<int> &nums2,
                            const int n);

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