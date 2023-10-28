#include "leetcode.h"
#include <algorithm>
#include <map>
#include <numeric>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

namespace leetcode = lawrencium::leetcode;

void leetcode::MergeSortedArraysNaive(std::vector<int> *nums1,
                                      const int m,
                                      const std::vector<int> &nums2,
                                      const int n) {
  // Shift the elements in nums1 s.t. we get the space to potentially copy the
  // entirety of nums2 at the start of nums1.
  for (auto i = m - 1; i >= 0; i--) {
    nums1->at(i + n) = nums1->at(i);
  }
  int nums1_index = n;
  int nums2_index = 0;
  int target_index = 0;
  while (true) {
    if (nums2_index == n)
      break;
    if (nums1_index == n + m) {
      nums1->at(target_index) = nums2[nums2_index];
      nums2_index += 1;
    } else {
      const auto e_1 = nums1->at(nums1_index);
      const auto e_2 = nums2.at(nums2_index);
      if (e_1 <= e_2) {
        nums1->at(target_index) = e_1;
        nums1_index += 1;
      } else {
        nums1->at(target_index) = e_2;
        nums2_index += 1;
      }
    }

    target_index += 1;
  }
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
  std::inclusive_scan(++str.cbegin(),
                      str.cend(),
                      ++leftScan.begin(),
                      updateState,
                      initialLeftState);
  auto rightScan = std::vector<State>(inputSize);
  auto initialRightState = State{.character = str[inputSize - 1], .count = 1};
  rightScan[inputSize - 1] = initialRightState;
  std::inclusive_scan(++str.crbegin(),
                      str.crend(),
                      ++rightScan.rbegin(),
                      updateState,
                      initialRightState);
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