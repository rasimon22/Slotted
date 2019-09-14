//
// Created by rasimon on 9/12/19.
//

#include "Timer.h"
#include <iostream>

std::map<std::string, unsigned long long> Chron::Timer::times;

Chron::Timer::Timer(const char *str) : run(std::string(str)), start(), finish() {
  clock_gettime(CLOCK_MONOTONIC, &start);
}

Chron::Timer::Timer(std::string run) : run(std::move(run)), start(), finish() {
  clock_gettime(CLOCK_MONOTONIC, &start);
}

Chron::Timer::~Timer() {
  clock_gettime(CLOCK_MONOTONIC, &finish);
  Timer::times[this->run] = ((this->finish.tv_sec * 1000000000) + this->finish.tv_nsec) \
 - ((this->start.tv_sec * 1000000000) + this->start.tv_nsec);

}

unsigned long long Chron::Timer::duration(const std::string &str, Chron::Scale scale) {
  //call implementation with c_string
  return duration(str.c_str(), scale);

}

unsigned long long Chron::Timer::duration(const char *str, Chron::Scale scale) {
  std::string key(str);
  switch (scale) {
    case Chron::Scale::Seconds: {
      return Chron::Timer::times.find(key)->second / 1000000000;
    }

    case Chron::Scale::Milliseconds : {
      return Chron::Timer::times.find(key)->second / 1000000;
    }

    case Chron::Scale::Nanoseconds : {
      return Chron::Timer::times.find(key)->second;
    }

    default:
      return Chron::Timer::times.find(key)->second / 1000000;
  }
}
