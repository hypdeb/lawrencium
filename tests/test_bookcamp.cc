#include "bookcamp/pascals_triangle.h"
#include <gtest/gtest.h>

namespace bookcamp = lawrencium::bookcamp;

TEST(TestGenerateTriangle, GeneratesTriangle) {
  const auto triangle = bookcamp::generate_triangle(100);
}