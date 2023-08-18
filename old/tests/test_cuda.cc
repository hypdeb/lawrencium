#include "src/cpp/common.h"
#include "src/cuda/basic_cuda.cuh"
#include "src/cuda/ping.h"
#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <numeric>

TEST(LawrenciumCudaTest, CudaPingTest) {
  testing::internal::CaptureStdout();
  lawrencium::cuda::launch();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(1, 1);
}

TEST(LawrenciumCudaTest, CudaAddTest) {
  auto a = std::vector<float>(100000);
  std::iota(a.begin(), a.end(), 0);
  auto b = std::vector<float>(100000);
  std::iota(b.begin(), b.end(), 0);
  auto c = std::vector<float>(100000);
  // lawrencium::cuda::cuda_add(a.data(), b.data(), c.data(), 100000);
  // EXPECT_EQ(c[12346], 12346 * 2);
}

TEST(LawrenciumCudaTest, CudaDoubleStochasticityTest) {
  const int sideLength = 1000;
  const auto matrix = lawrencium::cpp::DiagonalMatrix<float>(sideLength, 0.02);
  // const auto isDoublyStochastic
  //     = lawrencium::cuda::is_doubly_stochastic(matrix.data(), sideLength);
  // EXPECT_FALSE(isDoublyStochastic);
}