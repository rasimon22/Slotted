#include <iostream>
#include "Timer.h"
#include <string>
#include <unistd.h>
#include "DataGen.h"
#include "AdjacencyList.h"
#include <string>
#include <stdlib.h>
#include <vector>
void test_with_uniform(int c, int s, int k, std::string dist) {

    Chron::Timer main_t(std::string("uniform_timer"));
    {
    DataGen<size_t, Distribution::Uniform> gen(1,c - 1);

    AdjacencyList a1(c);
    for (int i = 0; i < s; ++ i) {
        //for each student
        std::vector<size_t> classes;
        for (int j = 0; j < k; ++j) {
            //for classes per student
            //pick a random class
            classes.push_back(gen.yield());
        }

        for (int k = 0; k < classes.size(); ++k) {
            //iterate over each class per student
            for (int l = k; l < classes.size(); ++l) {
                //make edge for all other classes in students
                //schedule
                if(classes[k] != classes[l]) a1.insert(classes[k], classes[l]);
            }
        }
    }
    a1.print();
  }

std::cout << Chron::Timer::duration(std::string("linear_timer"), Chron::Scale::Nanoseconds) \
    << std::endl;
}
void test_with_normal(int c, int s, int k, std::string dist) {

    Chron::Timer main_t(std::string("normal_timer"));
    {
    DataGen<size_t, Distribution::Uniform> gen(1,c);

    AdjacencyList a1(c);
    for (int i = 0; i < s; ++ i) {
        //for each student
        std::vector<size_t> classes;
        for (int j = 0; j < k; ++j) {
            //for classes per student
            //pick a random class
            classes.push_back(rand_normal(c/2, 2.0));
        }

        for (int k = 0; k < classes.size(); ++k) {
            //iterate over each class per student
            for (int l = k; l < classes.size(); ++l) {
                //make edge for all other classes in students
                //schedule
                if(classes[k] != classes[l]) a1.insert(classes[k], classes[l]);
            }
        }
    }
    a1.print();
  }

std::cout << Chron::Timer::duration(std::string("linear_timer"), Chron::Scale::Nanoseconds) \
    << std::endl; 
}

void test_with_linear(int c, int s, int k, std::string dist) {
    {
    Chron::Timer main_t(std::string("linear_timer"));
    DataGen<size_t, Distribution::Uniform> gen(1,c-1);
    DataGen<size_t, Distribution::Uniform> gen2(1,c-1);

    AdjacencyList a1(c);
    for (int i = 0; i < s; ++ i) {
        //for each student
        std::vector<size_t> classes;
        for (int j = 0; j < k; ++j) {
            //for classes per student
            //pick a random class
            classes.push_back(DataGen<size_t, Distribution::Uniform>::rand_linear(gen,gen2));
        }

        for (int k = 0; k < classes.size(); ++k) {
            //iterate over each class per student
            for (int l = k; l < classes.size(); ++l) {
                //make edge for all other classes in students
                //schedule
                if(classes[k] != classes[l]) a1.insert(classes[k], classes[l]);
            }
        }
    }
    a1.print();
  }

  std::cout << Chron::Timer::duration(std::string("linear_timer"), Chron::Scale::Nanoseconds) << std::endl; 
}

int main(int argc, char *argv[]) {

  {
    Chron::Timer main_t(std::string("Main_timer"));
    std::cout << "Hello, World!" << std::endl;
    usleep(100000);
    std::cout << "C: " << argv[1] << std::endl;
    size_t c = atoi(argv[1]);
    std::cout << "S: " << argv[2] << std::endl;
    size_t s = atoi(argv[2]);
    std::cout << "K: " << argv[3] << std::endl;
    size_t k = atoi(argv[3]);
    std::cout << "DIST: " << argv[4] << std::endl;
    std::string dist = std::string(argv[4]);
    test_with_linear(c, s, k, dist);
    std::cout << std::endl;
    test_with_uniform(c, s, k, dist);
    std::cout << std::endl;
    test_with_normal(c, s, k, dist);
  std::cout << Chron::Timer::duration(std::string("Main_timer"), Chron::Scale::Nanoseconds) \
      << std::endl;
  return 0;
  }
}
