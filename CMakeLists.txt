cmake_minimum_required( VERSION 3.28 )

project( zlab )

set(POSSIBLE_CXX_STANDARDS 11 14 17 20 23)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "Choose C++ standard")
set_property(CACHE CMAKE_CXX_STANDARD PROPERTY STRINGS ${POSSIBLE_CXX_STANDARDS})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable( program main.cpp )

add_subdirectory( src )
target_link_libraries( program PRIVATE zlab )


# Testing
include(CTest)

find_package(GTest CONFIG REQUIRED)

add_executable( unit_tests test/my_tests.cpp )
target_link_libraries( unit_tests PRIVATE zlab GTest::gtest_main GTest::gtest)

include(GoogleTest)
gtest_discover_tests(unit_tests)
