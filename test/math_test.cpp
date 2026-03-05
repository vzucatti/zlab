
#include "math.hpp"

#include "core.hpp"
#include "gtest/gtest.h"

TEST(FastPowerFunction, PositiveExponent)
{
    auto expectedValue = zlab::pow(2.0, 2);
    auto actualValue = zlab::scalarType{4};
    auto tolerance = zlab::evaluate_safe_tolerance();
    EXPECT_NEAR(expectedValue, actualValue, tolerance);
}

TEST(FastPowerFunction, NegativeExponent)
{
    auto expectedValue = zlab::pow(2.0, -2);
    auto actualValue = zlab::scalarType{1} / 4;
    auto tolerance = zlab::evaluate_safe_tolerance();
    EXPECT_NEAR(expectedValue, actualValue, tolerance);
}
