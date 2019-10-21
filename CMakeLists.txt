cmake_minimum_required(VERSION 3.00)
project(Slotted)

set(CMAKE_CXX_STANDARD 11)

add_executable(Slotted main.cpp catch.hpp DataGen.h AdjacencyList.h AdjacencyList.cpp)
add_executable(Test Timer.cpp Timer.h Timer.cpp catch.hpp TimerTest.cpp TestMain.cpp DataGen.h DataGenTest.cpp AdjacencyList.h AdjacencyList.cpp)
add_library(Timer SHARED Timer.h Timer.cpp)
target_link_libraries(Slotted Timer)
