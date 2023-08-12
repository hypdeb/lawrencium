#include "src/cpp/common.h"
#include "src/cpp/matrixes.h"
#include <gtest/gtest.h>
#include <vector>

TEST(TestNothing, TestNothing) {
  const int sideLength = 1000;
  const int numElements = sideLength * sideLength;
  EXPECT_EQ(numElements, 1000000);
}

TEST(TestDiagonalMatrix, TestDiagonalMatrix) {
  const int sideLength = 5000;
  const auto matrix
      = lawrencium::cpp::matrixes::DiagonalMatrix<float>(sideLength, 0.02);
}

TEST(TestDiagonalMatrixRawLoop, TestDiagonalMatrixRawLoop) {
  const int sideLength = 5000;
  const auto matrix
      = lawrencium::cpp::DiagonalMatrixRawLoop<float>(sideLength, 0.02);
}
