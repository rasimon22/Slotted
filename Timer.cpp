//
// Created by rasimon on 9/12/19.
//

#include "Timer.h"
#include <iostream>

std::map<std::string, long> Chron::Timer::times;

Chron::Timer::Timer(std::string run) : run(run)
{
  clock_gettime(CLOCK_MONOTONIC, &start);
}

Chron::Timer::~Timer()
{
  clock_gettime(CLOCK_MONOTONIC, &finish);
  Timer::times[this->run] =  this->finish.tv_nsec - this->start.tv_nsec;

}

long Chron::Timer::duration(const std::string& key, Chron::Scale scale)
{
  switch (scale)
  {
    case Chron::Scale::Seconds:
    {
      return Chron::Timer::times.find(key)->second / 1000000000;
    }

    case Chron::Scale::Milliseconds :
    {
      return Chron::Timer::times.find(key)->second / 1000000;
    }

    case Chron::Scale::Nanoseconds :
    {
      return Chron::Timer::times.find(key)->second;
    }

    default:
      return Chron::Timer::times.find(key)->second /1000000;
  }
}
