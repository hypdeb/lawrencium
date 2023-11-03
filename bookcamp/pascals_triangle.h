#ifndef _LAWRENCIUM_BOOKCAMP_PASCALS_TRIANGLEW_H_
#define _LAWRENCIUM_BOOKCAMP_PASCALS_TRIANGLE_H_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &s,
                         const std::vector<std::vector<T>> &triangle) {
  for (const auto &row : triangle) {
    std::ranges::copy(row, std::ostream_iterator<T>(s, " "));
    s << '\n';
  }

  return s;
}

namespace lawrencium {
namespace bookcamp {

void generate_triangle_1();

std::vector<int> get_next_row(const std::vector<int> &last_row);

std::vector<std::vector<int>> generate_triangle_copy(int number_of_rows);

std::vector<std::vector<int>> generate_triangle(int number_of_rows);

} // namespace bookcamp
} // namespace lawrencium
#endif