
option( USE_SYSTEM_GTEST ON )

if( USE_SYSTEM_GTEST )
    find_package( GTest CONFIG REQUIRED QUIET COMPONENTS gtest gtest_main )
endif()

if( TARGET GTest::gtest )
    message( STATUS "Using GoogleTest provided by the system or package manager." )
else()
    message( STATUS "Fetching GoogleTest and making it available.")
    include( FetchContent )
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable( googletest )
endif()

add_executable( 
    unit_tests
        rbf_test.cpp
        math_test.cpp
        zmatrix_test.cpp
        ode_test.cpp
        solvers_test.cpp
)
target_link_libraries(
    unit_tests 
        PRIVATE 
            zlab
            GTest::gtest_main
            GTest::gtest
)

include( GoogleTest )
gtest_discover_tests( unit_tests )
