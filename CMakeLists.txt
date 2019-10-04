cmake_minimum_required(VERSION 3.15)
project(Slotted)

set(CMAKE_CXX_STANDARD 11)

add_executable(Slotted main.cpp Timer.cpp Timer.h catch.hpp DataGen.h )
add_executable(Test Timer.cpp Timer.h Timer.cpp catch.hpp TimerTest.cpp TestMain.cpp DataGen.h DataGenTest.cpp)
add_library(Timer SHARED Timer.h Timer.cpp)
