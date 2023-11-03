#include "ita/sorting.h"
#include <gtest/gtest.h>
#include <span>
#include <vector>

namespace ita = lawrencium::ita;

TEST(TestQuickSort, EmptyArray) {
  auto input = std::vector<int>{};
  auto span = std::span(input);
  ita::quick_sort(span);
  EXPECT_EQ(input.size(), 0);
}