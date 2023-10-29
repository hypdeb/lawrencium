#ifndef _LAWRENCIUM_BOOKCAMP_HELLO_WORLD_H_
#define _LAWRENCIUM_BOOKCAMP_HELLO_WORLD_H_

namespace lawrencium {
namespace bookcamp {
template <typename T, typename U>
auto simple_plus(T lhs, U rhs) -> decltype(lhs + rhs) {
  return lhs + rhs;
};
} // namespace bookcamp
} // namespace lawrencium
#endif