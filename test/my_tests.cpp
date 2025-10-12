#include "gtest/gtest.h"

// Define a simple test fixture if you need setup/teardown (optional for trivial tests)
// For now, we'll just use a direct test case.

// TEST(TestSuiteName, TestName)
TEST(TrivialTest, SimpleAssertion) {
    int expected_value = 42;
    int actual_value = 42;

    // ASSERT_EQ checks if the two values are equal. If not, the test fails immediately.
    ASSERT_EQ(expected_value, actual_value);
}

// Another example that is guaranteed to pass
TEST(TrivialTest, BooleanCheck) {
    bool is_ready = true;
    
    // EXPECT_TRUE checks if the condition is true. 
    // If it fails, the test continues executing (unlike ASSERT_*)
    EXPECT_TRUE(is_ready);
}

// Note: You do not need a main() function here.
// GTest::gtest_main (which you linked in CMake) provides the main() entry point.
