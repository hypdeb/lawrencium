#include "src/cpp/common.h"
#include "src/cpp/matrixes.h"
#include <gtest/gtest.h>
#include <ranges>
#include <vector>

TEST(TestNothing, TestNothing) {
  const int sideLength = 1000;
  const int numElements = sideLength * sideLength;
  EXPECT_EQ(numElements, 1000000);
}

TEST(TestDiagonalMatrix, TestDiagonalMatrix) {
  const uint sideLength = 5000;
  const auto matrix = lawrencium::cpp::matrixes::DiagonalMatrix<float, uint>(
      sideLength, 0.02);
}

TEST(TestDiagonalMatrix, TestDiagonalMatrixFromValues) {
  const uint sideLength = 3;
  const std::ranges::range<float> auto diagonalValues
      = std::vector<float>{0.02, 0.03, 0.04};
  const auto matrix = lawrencium::cpp::matrixes::DiagonalMatrixFromValues(
      sideLength, diagonalValues);
}

TEST(TestDiagonalMatrixRawLoop, TestDiagonalMatrixRawLoop) {
  const int sideLength = 5000;
  const auto matrix
      = lawrencium::cpp::DiagonalMatrixRawLoop<float>(sideLength, 0.02);
}
