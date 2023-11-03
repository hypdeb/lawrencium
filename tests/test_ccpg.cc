#include "ccpg/julia.h"
#include "ccpg/matrixes.h"
#include "ccpg/vectors.h"
#include "common/utils.h"
#include <cuda_runtime.h>
#include <gtest/gtest.h>
#include <vector>

TEST(TestMatrixMultiply, RunsAtAll) {
  cudaDeviceReset();
  auto lh_elements = lawrencium::common::RandomVector(512 * 512);
  const auto lh = lawrencium::ccpg::library::matrix{
      .width = 512,
      .height = 512,
      .elements = lh_elements.data(),
  };
  auto rh_elements = lawrencium::common::RandomVector(512 * 512);
  const auto rh = lawrencium::ccpg::library::matrix{
      .width = 512,
      .height = 512,
      .elements = rh_elements.data(),
  };
  auto result_elements = std::vector<float>(512 * 512);
  auto result = lawrencium::ccpg::library::matrix{
      .width = 512,
      .height = 512,
      .elements = result_elements.data(),
  };

  lawrencium::ccpg::library::MatMul(lh, rh, result);
  EXPECT_EQ(1, 1);
}

TEST(TestSharedMemoryMatMul, RunsAtAll) {
  cudaDeviceReset();
  auto lh_elements = lawrencium::common::RandomVector(512 * 512);
  const auto lh = lawrencium::ccpg::library::matrix{
      .width = 512,
      .height = 512,
      .elements = lh_elements.data(),
  };
  auto rh_elements = lawrencium::common::RandomVector(512 * 512);
  const auto rh = lawrencium::ccpg::library::matrix{
      .width = 512,
      .height = 512,
      .elements = rh_elements.data(),
  };
  auto result_elements = std::vector<float>(512 * 512);
  auto result = lawrencium::ccpg::library::matrix{
      .width = 512,
      .height = 512,
      .elements = result_elements.data(),
  };

  lawrencium::ccpg::library::SharedMemoryMatMul(lh, rh, result);
  EXPECT_EQ(1, 1);
}

TEST(TestVectorAdd, RunsAtAll) {
  cudaDeviceReset();
  auto lh_elements = lawrencium::common::RandomVector(512 * 512);
  const auto lh = lawrencium::ccpg::library::GpuVector{
      .length = 512 * 512,
      .elements = lh_elements.data(),
  };
  auto rh_elements = lawrencium::common::RandomVector(512 * 512);
  const auto rh = lawrencium::ccpg::library::GpuVector{
      .length = 512 * 512,
      .elements = rh_elements.data(),
  };
  auto result_elements = std::vector<float>(512 * 512);
  auto result = lawrencium::ccpg::library::GpuVector{
      .length = 512 * 512,
      .elements = result_elements.data(),
  };

  lawrencium::ccpg::library::AddVectors(lh, rh, result);
  EXPECT_EQ(1, 1);
}

TEST(TestJuliaSet, RunsAtAll) {
  cudaDeviceReset();
  lawrencium::ccpg::julia::DrawOnGpu(2048);
  EXPECT_EQ(1, 1);
}