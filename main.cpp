#include <iostream>
#include "Timer.h"
#include <string>
#include <unistd.h>

int main() {
  {
    Chron::Timer main_t(std::string("Main_timer"));
    std::cout << "Hello, World!" << std::endl;
    usleep(100000000);

  }
    std::cout << Chron::Timer::duration(std::string("Main_timer"), Chron::Scale::Nanoseconds) << std::endl;
  return 0;
}