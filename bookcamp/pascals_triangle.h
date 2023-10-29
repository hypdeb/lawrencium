#ifndef _LAWRENCIUM_BOOKCAMP_PASCALS_TRIANGLEW_H_
#define _LAWRENCIUM_BOOKCAMP_PASCALS_TRIANGLE_H_

#include <vector>

namespace lawrencium {
namespace bookcamp {

void generate_triangle_1();

std::vector<int> get_next_row(const std::vector<int> &last_row);

std::vector<std::vector<int>> generate_triangle_copy(int number_of_rows);

std::vector<std::vector<int>> generate_triangle(int number_of_rows);

} // namespace bookcamp
} // namespace lawrencium
#endif