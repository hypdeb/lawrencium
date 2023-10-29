#ifndef _LAWRENCIUM_CTCI_H_
#define _LAWRENCIUM_CTCI_H_

#include <iostream>

#define NAME_SIZE 50 // Define a macro.

namespace lawrencium {
namespace ctci {

class Person {
  int id; // All members are private by default.
  char name[NAME_SIZE];

public:
  void AboutMe();
}

class Student : public Person {
public:
  void AboutMe();
}

} // namespace ctci
} // namespace lawrencium

#endif