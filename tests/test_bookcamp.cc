#include "bookcamp/pascals_triangle.h"
#include <gtest/gtest.h>
#include <iostream>

namespace bookcamp = lawrencium::bookcamp;

TEST(TestGenerateTriangle, GeneratesTriangle) {
  auto triangle = bookcamp::generate_triangle(10);
  std::cout << triangle;
}