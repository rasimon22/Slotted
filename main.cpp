#include <iostream>
#include "Timer.h"
#include <string>

int main() {
  {
    Chron::Timer main_t(std::string("Main_timer"));
    std::cout << "Hello, World!" << std::endl;
    for (int i = 0; i < 100; ++i);
  }
    std::cout << Chron::Timer::duration(std::string("Main_timer"), Chron::Scale::Nanoseconds) << std::endl;
  return 0;
}