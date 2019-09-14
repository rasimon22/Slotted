cmake_minimum_required(VERSION 3.15)
project(Slotted)

set(CMAKE_CXX_STANDARD 11)

add_executable(Slotted main.cpp Timer.cpp Timer.h catch.hpp)
add_executable(Test Timer.cpp Timer.h Timer.cpp catch.hpp TimerTest.cpp TestMain.cpp)
