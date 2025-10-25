cmake_minimum_required( VERSION 3.28 )

project( zlab )

set( POSSIBLE_CXX_STANDARDS 11 14 17 20 23 )
set( CMAKE_CXX_STANDARD 20 CACHE STRING "Choose C++ standard" )
set_property( CACHE CMAKE_CXX_STANDARD PROPERTY STRINGS ${POSSIBLE_CXX_STANDARDS} )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

add_subdirectory( src )

option( ADD_EIGEN TRUE )
if( ADD_EIGEN )
    option( USE_SYSTEM_EIGEN ON )
    if( USE_SYSTEM_EIGEN )
        find_package( Eigen3 CONFIG QUIET )
    endif()
    if( TARGET Eigen3::Eigen )
        message( STATUS "Using Eigen provided by the system or package manager." )
    else()
        message( STATUS "Fetching Eigen and making it available." )
        include( FetchContent )
        FetchContent_Declare(
            eigen
            GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
            GIT_TAG     3.4.0
        )
        FetchContent_MakeAvailable( eigen )
    endif()
endif()

option( BUILD_TESTING "Build unit tests" ON )
if( BUILD_TESTING )
    include( CTest )
    add_subdirectory( test )
endif()

option( BUILD_EXAMPLES "Build examples" ON )
if( BUILD_EXAMPLES)
    add_subdirectory( examples )
endif()
