add_executable(hashmap_tests_run hashMapTest.cpp catch_main.cpp ../Suggestions.h TST_Test.cpp)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wconversion -Wextra -pedantic")
#With coverage
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wconversion -Wextra -pedantic --coverage")