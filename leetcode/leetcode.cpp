#include "leetcode.h"
#include <algorithm>
#include <map>
#include <numeric>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

namespace leetcode = lawrencium::leetcode;

std::vector<int>
leetcode::MergeSortedArraysNaive(const std::vector<int> &nums1,
                                 const std::vector<int> &nums2) {
  const auto result_size = nums1.size() + nums2.size();
  auto result = std::vector<int>(result_size);

  auto iter1 = nums1.cbegin();
  auto iter2 = nums2.cbegin();
  auto resultIter = result.begin();
  const auto end1 = nums1.cend();
  const auto end2 = nums2.cend();

  // While we have not reached the end of either of the inputs.
  while (iter1 != end1 && iter2 != end2) {
    if (*iter1 <= *iter2) {
      *resultIter = *iter1;
      std::advance(iter1, 1);
    } else {
      *resultIter = *iter2;
      std::advance(iter2, 1);
    }
    std::advance(resultIter, 1);
  }

  // If we have reached the end of nums1 first, fill the rest of the results
  // with the remaining elements of nums2.
  if (iter1 == nums1.cend()) {
    while (iter2 != nums2.cend()) {
      *resultIter = *iter2;
      std::advance(iter2, 1);
      std::advance(resultIter, 1);
    }
  } else {
    while (iter1 != nums1.cend()) {
      *resultIter = *iter1;
      std::advance(iter1, 1);
      std::advance(resultIter, 1);
    }
  }

  return result;
}

int leetcode::CountBinarySubstrings(const std::string &str) {
  struct State {
    char character;
    int count;
  };

  auto updateState = [](const auto &state, const auto c) {
    if (state.character == c) {
      return State{.character = state.character, .count = state.count + 1};
    } else {
      return State{.character = c, .count = 1};
    }
  };

  auto inputSize = str.size();
  if (inputSize < 2)
    return 0;
  auto leftScan = std::vector<State>(inputSize);
  auto initialLeftState = State{.character = str[0], .count = 1};
  leftScan[0] = initialLeftState;
  std::inclusive_scan(++str.cbegin(), str.cend(), ++leftScan.begin(),
                      updateState, initialLeftState);
  auto rightScan = std::vector<State>(inputSize);
  auto initialRightState = State{.character = str[inputSize - 1], .count = 1};
  rightScan[inputSize - 1] = initialRightState;
  std::inclusive_scan(++str.crbegin(), str.crend(), ++rightScan.rbegin(),
                      updateState, initialRightState);
  int count = 0;
  for (auto i = 0; i < inputSize - 1; i++) {
    const auto &leftScanValue = leftScan[i];
    const auto &rightScanValue = rightScan[i + 1];
    if (rightScanValue.character != leftScanValue.character) {
      count += std::min(rightScanValue.count, leftScanValue.count);
    }
  }

  return count;
}

int leetcode::LongestIncreasingPathInMatrix(
    std::vector<std::vector<int>> &matrix) {
  const auto numRows = matrix.size();
  if (numRows == 0)
    return 0;
  const auto numCols = matrix[0].size();
  if (numCols == 0)
    return 0;
  auto visitedCoordinates = std::map<std::tuple<int, int>, int>();
  for (auto i = 0; i < numRows; i++) {
    for (auto j = 0; j < numCols; j++) {
      auto coordinatesToExplore
          = std::stack<std::tuple<std::tuple<int, int>, int>>();
      // Try moving up and update.

      // Try moving right and update.

      // Try moving down and update.

      // Try moving left and update.
    }
  }

  return 0; // I will come back to this.
}