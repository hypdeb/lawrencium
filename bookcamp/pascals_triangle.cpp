#include "pascals_triangle.h"
#include <iostream>
#include <vector>
namespace bookcamp = lawrencium::bookcamp;

void bookcamp::generate_triangle_1() {
  std::vector<int> data{1};
  for (const auto number : data) {
    std::cout << number << ' ';
  }
}

std::vector<int> bookcamp::get_next_row(const std::vector<int> &last_row) {
  std::vector next_row{1};
  if (last_row.empty()) {
    return next_row;
  }

  for (auto idx = 0; idx + 1 < last_row.size(); ++idx) {
    next_row.emplace_back(last_row[idx] + last_row[idx + 1]);
  }

  next_row.emplace_back(1);
  return next_row;
}

std::vector<std::vector<int>>
bookcamp::generate_triangle_copy(int number_of_rows) {
  auto data = std::vector<int>{};
  auto triangle = std::vector<std::vector<int>>{};
  for (int row_index = 0; row_index < number_of_rows; ++row_index) {
    data = bookcamp::get_next_row(data);
    triangle.push_back(data);
  }

  return triangle;
}

std::vector<std::vector<int>> bookcamp::generate_triangle(int number_of_rows) {
  auto triangle = std::vector<std::vector<int>>{{1}};
  for (int row_index = 0; row_index < number_of_rows; ++row_index) {
    triangle.push_back(bookcamp::get_next_row(triangle.back()));
  }

  return triangle;
}