#include "ccpg/matrix_multiply.h"
#include <cuda_runtime.h>
#include <gtest/gtest.h>
#include <vector>

TEST(TestMatrixMultiply, RunsAtAll) {
  cudaDeviceReset();
  auto lh_elements = std::vector<float>{1, 0, 0, 1};
  const auto lh = lawrencium::ccpg::library::matrix{
      .width = 2,
      .height = 2,
      .elements = lh_elements.data(),
  };
  auto rh_elements = std::vector<float>{1, 0, 0, 1};
  const auto rh = lawrencium::ccpg::library::matrix{
      .width = 2,
      .height = 2,
      .elements = rh_elements.data(),
  };
  auto result_elements = std::vector<float>(4);
  auto result = lawrencium::ccpg::library::matrix{
      .width = 2,
      .height = 2,
      .elements = result_elements.data(),
  };

  lawrencium::ccpg::library::MatMul(lh, rh, result);
  EXPECT_EQ(result.elements[0], 1);
  EXPECT_EQ(result.elements[1], 0);
  EXPECT_EQ(result.elements[2], 0);
  EXPECT_EQ(result.elements[3], 1);
}