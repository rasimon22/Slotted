//
// Created by rasimon on 9/30/19.
//

#include "catch.hpp"
#include "DataGen.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>


TEST_CASE("DataGenTest") {

  DataGen<int, Distribution::Uniform> gen(0, 100);
  for (auto i = 0; i < 100; ++i) {
    std::cout << gen.getData()[i] << ' ';
  }

  short hits = 0;
  for(int i = 0; i < 10; ++i) {
    DataGen<float, Distribution::Uniform> gen(0, 100);
    usleep(1000000); //sleep to allow rng to re-seed
    DataGen<float, Distribution::Uniform> gen_2(0, 100);
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
  DataGen<float, Distribution::Uniform> gen(0, 100);
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
  auto total = 0;
  for(auto i = 0; i < 100; ++i) {
    int gen = rand_normal(50.0, 10.0);
    total += gen;
  }
  REQUIRE(abs(total/100 - 50) < 5.0);
}

TEST_CASE("Datagen_Yield") {
  DataGen<float, Distribution::Uniform> gen(0, 100);
  for(int i = 0; i < 1000; ++i){
    gen.yield();
  }
  //non crash passses
  REQUIRE(true);
}

TEST_CASE("DataGen_Linear") {
    std::unique_ptr<int[]> ticks(new int[101]);
    DataGen<int, Distribution::Uniform> gen(0, 100);
    DataGen<int, Distribution::Uniform> gen2(0, 100);
    for(int i = 0; i < 100; ++i) {
        ticks[i] = 0;
    }
    for(int i = 0; i < 2000000; ++i) {
        ticks[DataGen<int, Distribution::Uniform>::rand_linear(gen, gen2)]++;
    }
    for(int i = 0; i < 99; ++i) {
        std::cout << ticks[i] << std::endl;
        REQUIRE(ticks[i] <= ticks[i+1]);
    }
}

