cmake_minimum_required(VERSION 3.15)
project(ASD2_Labs_2020)

set(CMAKE_CXX_STANDARD 11)

add_executable(hashmap_main main.cpp HashMap/HashMapSeparateChaining.h HashMap/HashMapLinearProbing.h Dictionary.h TernarySearchTree.h HashMap/DictionaryContainer.h Utils/sanitizeWord.h)
add_subdirectory(catch2_tests)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wconversion -Wextra -pedantic")
