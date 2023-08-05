#include "src/cpp/common.h"
#include <gtest/gtest.h>
#include <vector>

TEST(TestNothing, TestNothing) {
  const int sideLength = 1000;
  const int numElements = sideLength * sideLength;
  EXPECT_EQ(numElements, 1000000);
}

TEST(TestDiagonalMatrix, TestDiagonalMatrix) {
  const int sideLength = 1000;
  const int numElements = sideLength * sideLength;
  const auto vec = std::vector<float>(numElements);
  const auto matrix = lawrencium::cpp::DiagonalMatrix<float>(sideLength, 0.02);
}
