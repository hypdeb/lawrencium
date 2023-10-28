#include "common/linked_list.h"
#include "leetcode/leetcode.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

using namespace testing;
namespace leetcode = lawrencium::leetcode;

TEST(TestMergeSortedArrays, BothParametersEmpty) {
  auto nums1 = std::vector<int>();
  const auto nums2 = std::vector<int>();
  leetcode::MergeSortedArraysNaive(&nums1, 0, nums2, 0);
  EXPECT_EQ(nums1.size(), 0);
}

TEST(TestMergeSortedArrays, FirstParameterEmpty) {
  auto nums1 = std::vector<int>(3);
  const auto nums2 = std::vector<int>{1, 2, 3};
  leetcode::MergeSortedArraysNaive(&nums1, 0, nums2, 3);
  EXPECT_EQ(nums1.size(), 3);
  ASSERT_THAT(nums1, ElementsAre(1, 2, 3));
}

TEST(TestMergeSortedArrays, SecondParameterEmpty) {
  auto nums1 = std::vector<int>{1, 2, 3};
  const auto nums2 = std::vector<int>();
  leetcode::MergeSortedArraysNaive(&nums1, 3, nums2, 0);
  EXPECT_EQ(nums1.size(), 3);
  ASSERT_THAT(nums1, ElementsAre(1, 2, 3));
}

TEST(TestMergeSortedArrays, FirstParameterShorter) {
  auto nums1 = std::vector<int>{1, 3, 0, 0, 0};
  const auto nums2 = std::vector<int>{2, 4, 5};
  leetcode::MergeSortedArraysNaive(&nums1, 2, nums2, 3);
  EXPECT_EQ(nums1.size(), 5);
  ASSERT_THAT(nums1, ElementsAre(1, 2, 3, 4, 5));
}

TEST(TestMergeSortedArrays, SecondParameterShorter) {
  auto nums1 = std::vector<int>{1, 3, 5, 0, 0};
  const auto nums2 = std::vector<int>{2, 4};
  leetcode::MergeSortedArraysNaive(&nums1, 3, nums2, 2);
  EXPECT_EQ(nums1.size(), 5);
  ASSERT_THAT(nums1, ElementsAre(1, 2, 3, 4, 5));
}

TEST(ReverseLinkedList, OneNode) {
  auto node = lawrencium::common::Node<int>{
      .data = 1,
      .next = nullptr,
  };
  auto reversed = leetcode::ReverseLinkedList(&node);
  EXPECT_EQ(reversed->data, 1);
  EXPECT_EQ(reversed->next, nullptr);
}

TEST(ReverseLinkedList, FewNodes) {
  auto lastNode = lawrencium::common::Node<int>{
      .data = 1,
      .next = nullptr,
  };
  auto middleNode = lawrencium::common::Node<int>{
      .data = 2,
      .next = &lastNode,
  };
  auto firstNode = lawrencium::common::Node<int>{
      .data = 3,
      .next = &middleNode,
  };
  auto reversedFirst = leetcode::ReverseLinkedList(&firstNode);
  EXPECT_EQ(reversedFirst->data, 1);
  EXPECT_EQ(reversedFirst->next, &middleNode);
  auto reversedMiddle = reversedFirst->next;
  EXPECT_EQ(reversedMiddle->data, 2);
  EXPECT_EQ(reversedMiddle->next, &firstNode);
  auto reversedLast = reversedMiddle->next;
  EXPECT_EQ(reversedLast->data, 3);
  EXPECT_EQ(reversedLast->next, nullptr);
}

TEST(CountBinarySubstrings, EmptyInput) {
  const auto input = "";
  const auto result = leetcode::CountBinarySubstrings(input);
  EXPECT_EQ(result, 0);
}

TEST(CountBinarySubstrings, OneCharacterInput) {
  const auto input = "1";
  const auto result = leetcode::CountBinarySubstrings(input);
  EXPECT_EQ(result, 0);
}

TEST(CountBinarySubstrings, TrivialTwoCharactersNoMatches) {
  const auto input = "11";
  const auto result = leetcode::CountBinarySubstrings(input);
  EXPECT_EQ(result, 0);
}

TEST(CountBinarySubstrings, TrivialTwoCharactersOneMatch) {
  const auto input = "10";
  const auto result = leetcode::CountBinarySubstrings(input);
  EXPECT_EQ(result, 1);
}

TEST(CountBinarySubstrings, StandardCase) {
  const auto input = "00110011";
  const auto result = leetcode::CountBinarySubstrings(input);
  EXPECT_EQ(result, 6);
}