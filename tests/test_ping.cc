#include <gtest/gtest.h>

// Checks that tests can be run at all.
TEST(PingTest, PingTest) {
  EXPECT_EQ(7 * 6, 42);
}