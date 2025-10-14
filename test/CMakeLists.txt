
find_package( GTest CONFIG REQUIRED )

add_executable( 
    unit_tests
        rbf_test.cpp
        math_test.cpp
        matrix_test.cpp
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
