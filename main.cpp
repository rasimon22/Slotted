#include <iostream>
#include "Timer.h"
#include <string>
#include <unistd.h>
#include "DataGen.h"
#include "AdjacencyList.h"
#include <string>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  {
    Chron::Timer main_t(std::string("Main_timer"));
    std::cout << "Hello, World!" << std::endl;
    usleep(100000);
    std::cout << "C: " << argv[1] << std::endl;
    size_t c = atoi(argv[1]);
    std::cout << "S: " << argv[2] << std::endl;
    size_t c = atoi(argv[2]);
    std::cout << "K: " << argv[3] << std::endl;
    size_t c = atoi(argv[3]);
    std::cout << "DIST: " << argv[4] << std::endl;
    std::string dist = std::string(argv[4]);
    DataGen<size_t, DistributionUniform> gen(0,c);

    AdjacencyList a1(c);
    a1.insert(1,2);
    a1.insert(1,3);
    a1.insert(1,3);
    a1.insert(1,3);
    a1.insert(1,3);
    a1.insert(1,4);
    a1.insert(1,4);
    a1.insert(1,4);
    a1.insert(9,3);
    a1.insert(9,3);
    a1.insert(9,1);
    a1.print();
  }
  std::cout << Chron::Timer::duration(std::string("Main_timer"), Chron::Scale::Nanoseconds) \
      << std::endl;
  return 0;
}
