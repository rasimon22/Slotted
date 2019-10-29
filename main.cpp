#include <iostream>
#include "Timer.h"
#include <string>
#include <unistd.h>
#include "DataGen.h"
#include "AdjacencyList.h"
#include <string>
#include <stdlib.h>
#include <vector>
#include <memory>
void test_with_uniform(int c, int s, int k, std::string dist) {

    {
    Chron::Timer main_t(std::string("uniform_timer"));
    DataGen<size_t, Distribution::Uniform> gen(1,c - 1);

    AdjacencyList a1(c);
    std::unique_ptr<int[]> duplicates(new int[c]);
    for(int i = 0; i < c; ++i){
        duplicates[i] = c*2;
    }
    for (int i = 0; i < s; ++ i) {
        //for each student
        std::vector<size_t> classes;
        for (int j = 0; j < k; ++j) {
            //for classes per student
            //pick a random class
            int rand = gen.yield();
            //guess again if duplicate
            while(duplicates[rand] == i){
                rand = gen.yield();
            }
            classes.push_back(rand);
            duplicates[rand] = i;
        }

//        for (int k = 0; k < classes.size(); ++k) {
//            //iterate over each class per student
//            for (int l = k; l < classes.size(); ++l) {
//                //make edge for all other classes in students
//                //schedule
//                if(classes[k] != classes[l]) a1.insert(classes[k], classes[l]);
//            }
//        }
    }
    a1.print();
  }

std::cout << Chron::Timer::duration(std::string("uniform_timer"), Chron::Scale::Milliseconds) \
    << "ns" << std::endl;
}
void test_with_normal(int c, int s, int k, std::string dist) {

    {

    Chron::Timer main_t(std::string("normal_timer"));
    DataGen<size_t, Distribution::Uniform> gen(1,c);
    std::unique_ptr<int[]> duplicates(new int[c]);
    for(int i = 0; i < c; ++i){
        duplicates[i] = c*2;
    }
    AdjacencyList a1(c);
    for (int i = 0; i < s; ++ i) {
        //for each student
        std::vector<size_t> classes;
        for (int j = 0; j < k; ++j) {
            //for classes per student
            //pick a random class
            int rand = rand_normal(c/2, c/4);
            while (duplicates[rand] == i) {
                rand = rand_normal(c/2, c/4);
            }
            classes.push_back(rand);
            duplicates[rand] = i;
        }

//        for (int k = 0; k < classes.size(); ++k) {
//            //iterate over each class per student
//            for (int l = k; l < classes.size(); ++l) {
//                //make edge for all other classes in students
//                //schedule
//                if(classes[k] != classes[l]) a1.insert(classes[k], classes[l]);
//            }
//        }
    }
    a1.print();
  }

std::cout << Chron::Timer::duration(std::string("normal_timer"), Chron::Scale::Nanoseconds) \
    << "ns" << std::endl; 
}

void test_with_linear(int c, int s, int k, std::string dist) {
    {
    Chron::Timer main_t(std::string("linear_timer"));
    DataGen<size_t, Distribution::Uniform> gen(1,c-1);
    DataGen<size_t, Distribution::Uniform> gen2(1,c-1);
    std::unique_ptr<int[]> duplicates(new int[c]);
    for(int i = 0; i < c; ++i) {
        duplicates[i] = c*2;
    }

    AdjacencyList a1(c);
    for (int i = 0; i < s; ++ i) {
        //for each student
        std::vector<size_t> classes;
        for (int j = 0; j < k; ++j) {
            //for classes per student
            //pick a random class
            int rand = DataGen<size_t, Distribution::Uniform>::rand_linear(gen,gen2);
            while(duplicates[rand] == i) {
                rand = DataGen<size_t, Distribution::Uniform>::rand_linear(gen,gen2);
            }
            classes.push_back(rand);
            duplicates[rand] = i;
        }

//        for (int k = 0; k < classes.size(); ++k) {
//            //iterate over each class per student
//            for (int l = k; l < classes.size(); ++l) {
//                //make edge for all other classes in students
//                //schedule
//                if(classes[k] != classes[l]) a1.insert(classes[k], classes[l]);
//            }
//        }
    }
    a1.print();
  }

  std::cout << Chron::Timer::duration(std::string("linear_timer"), Chron::Scale::Nanoseconds) << "ns" << std::endl; 
}
void test_with_tiered(int c, int s, int k, std::string dist) {
    {
    Chron::Timer main_t(std::string("tiered_timer"));
    DataGen<int, Distribution::Uniform> gen(1,(int)c/4);
    DataGen<int, Distribution::Uniform> gen2((int)c/4, (int)c/2);
    DataGen<int, Distribution::Uniform> gen3((int)c/2,(int)(3*c/4));
    DataGen<int, Distribution::Uniform> gen4((int)(3*c/4),c);
    std::unique_ptr<int[]> duplicates(new int[c]);
    for(int i = 0; i < c; ++i) {
        duplicates[i] = c*2;
    }
    int probs[4] = {10, 11, 13, 50 };
    AdjacencyList a1(c);
    for (int i = 0; i < s; ++ i) {
        //for each student
        std::vector<size_t> classes;
        for (int j = 0; j < k; ++j) {
            //for classes per student
            //pick a random class
            int rand = rand_tiered(gen, gen2, gen3, gen4, probs);
            while(duplicates[rand] == i) {
                rand =  rand_tiered(gen, gen2, gen3, gen4, probs);
            }
            classes.push_back(rand);
            duplicates[rand] = i;
        }

//        for (int k = 0; k < classes.size(); ++k) {
//            //iterate over each class per student
//            for (int l = k; l < classes.size(); ++l) {
//                //make edge for all other classes in students
//                //schedule
//                if(classes[k] != classes[l]) a1.insert(classes[k], classes[l]);
//            }
//        }
    }
    a1.print();
  }

  std::cout << Chron::Timer::duration(std::string("tiered_timer"), Chron::Scale::Nanoseconds) << "ns" << std::endl; 
}
int main(int argc, char *argv[]) {

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
    if (dist == "LINEAR"){ 
    test_with_linear(c, s, k, dist);
    std::cout << std::endl;
    }
    if (dist == "UNIFORM") {
    test_with_uniform(c, s, k, dist);
    std::cout << std::endl;
    }
    if (dist == "NORMAL") {
    test_with_normal(c, s, k, dist);
    std::cout << std::endl;
    }
    if (dist == "TIERED") {
    test_with_tiered(c, s, k, dist);
    std::cout << std::endl;
    }

  return 0;
}
