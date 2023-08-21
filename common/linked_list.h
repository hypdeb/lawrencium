#ifndef _LAWRENCIUM_COMMON_LINKED_LIST_H_
#define _LAWRENCIUM_COMMON_LINKED_LIST_H_

#include <concepts>

namespace lawrencium {
namespace common {
template <std::default_initializable T> struct Node {
  T data = T();
  Node *next = nullptr;
};
} // namespace common
} // namespace lawrencium

#endif