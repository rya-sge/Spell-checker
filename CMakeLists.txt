cmake_minimum_required(VERSION 3.15)
project(ASD2_Labs_2020)

set(CMAKE_CXX_STANDARD 11)

add_executable(hashmap_main main.cpp HashMapSeparateChaining.h HashMapLinearProbing.h)
add_subdirectory(catch2_tests)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wconversion -Wextra -pedantic")
