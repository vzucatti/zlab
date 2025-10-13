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

option( ADD_EIGEN TRUE )
if ( ADD_EIGEN )
    find_package(Eigen3 REQUIRED)
    target_link_libraries( program PRIVATE Eigen3::Eigen )
endif()

option(BUILD_TESTING "Build unit tests" ON)
if (BUILD_TESTING)
    include( CTest )
    add_subdirectory(test)
endif()
