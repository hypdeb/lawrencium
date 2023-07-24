#include "src/cuda/ping.h"
#include <gtest/gtest.h>

// Checks that tests can be run at all.
TEST(PingTest, PingTest) { EXPECT_EQ(7 * 6, 42); }

// Checks that CUDA code can be run at all.
TEST(CudaPingTest, CudaPingTest) { cuda::launch(); }