#include "ctci.h"
#include <iostream>

namespace ctci = lawrencium::ctci;

void ctci::Person::AboutMe() { std::cout << "I am a person."; }

void ctci::Student::AboutMe() { std::cout << "I am a student."; }