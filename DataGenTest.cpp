//
// Created by rasimon on 9/30/19.
//

#include "catch.hpp"
#include "DataGen.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <set>


TEST_CASE("DataGenTest") {

  DataGen<int, Distribution::Uniform> gen((size_t)100);
  for (auto i = 0; i < 100; ++i) {
    std::cout << gen.getData()[i] << ' ';
  }

  short hits = 0;
  for(int i = 0; i < 10; ++i) {
    DataGen<float, Distribution::Uniform> gen((size_t)100);
    usleep(1000000); //sleep to allow rng to re-seed
    DataGen<float, Distribution::Uniform> gen_2((size_t)100);
    bool match = true;
    for(int j = 0; j < 100; ++j) {
      if(gen.getData()[j] != gen_2.getData()[j]){
        match = false;
        break;
      }
    }
    if (match) ++hits;
  }
  REQUIRE(hits < 2);
}

TEST_CASE("DataGen_Regen") {
  DataGen<float, Distribution::Uniform> gen((size_t) 100);
  for(int i = 0; i < 100; ++i) {
    std::unique_ptr<float[]> data(new float[100]);
    std::copy(gen.getData(), gen.getData() + (sizeof(float) * 100), data.get());
    gen.regen();
    bool match = true;
    for (int j = 0; j < 100; ++j) {
      if (gen.getData()[j] != data[j]) {
        match = false;
        break;
      }
    }
    REQUIRE(!match);
  }
}

TEST_CASE("Datagen_Normal") {
//  rand_normal(50.0, 10.0);
  std::set<double> values;
  auto total = 0;
  for(auto i = 0; i < 100; ++i) {
    auto gen = rand_normal(50.0, 10.0);
    values.insert(gen);
    total += gen;
  }
  REQUIRE(abs(total/100 - 50) < 5.0);
//  for(auto kv : counts) {
//    std::cout << "Value: " << kv.first << " Count: " << kv.second << std::endl;
//  }


}