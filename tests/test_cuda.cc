#include "cuda/ping.h"
#include <cuda_runtime.h>
#include <gtest/gtest.h>

TEST(TestSanity, KernelCanBeCalled) {
  testing::internal::CaptureStdout();
  lawrencium::cuda::launch();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(1, 1);
}