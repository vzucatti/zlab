cmake_minimum_required( VERSION 3.28 )

project( zlab )

set( POSSIBLE_CXX_STANDARDS 11 14 17 20 23 )
set( CMAKE_CXX_STANDARD 20 CACHE STRING "Choose C++ standard" )
set_property( CACHE CMAKE_CXX_STANDARD PROPERTY STRINGS ${POSSIBLE_CXX_STANDARDS} )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

add_subdirectory( src )

option( ADD_EIGEN TRUE )
if ( ADD_EIGEN )
    find_package( Eigen3 REQUIRED )
endif()

option( BUILD_TESTING "Build unit tests" ON )
if ( BUILD_TESTING )
    include( CTest )
    add_subdirectory( test )
endif()

option( BUILD_EXAMPLES "Build examples" ON )
if( BUILD_EXAMPLES)
    add_subdirectory( examples )
endif()
