//
// Created by rasimon on 9/14/19.
//

#include "catch.hpp"
#include "Timer.h"
#include <iostream>
#include <unistd.h>


TEST_CASE("TimerTest") {
  {
    Chron::Timer main_t("Main_timer");
    usleep(100000);

  }

  REQUIRE(Chron::Timer::duration(std::string("Main_timer"), Chron::Scale::Seconds) == 0ull);
  REQUIRE(Chron::Timer::duration("Main_timer", Chron::Scale::Milliseconds) == 100ull);
  //Resolution of Nanoseconds higher than Microseconds, so we use inequality to account for overhead & cpu/wall time
  //difference. Default scale argument applied, is Chron::Scale::Nanoseconds
  REQUIRE(Chron::Timer::duration("Main_timer") - 100000000 < 1000000);
}