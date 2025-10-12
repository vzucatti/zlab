
#include "gtest/gtest.h"

#include "core.hpp"
#include "math.hpp"

TEST(FastPowerFunction, PositiveExponent) {
    auto expectedValue = zlab::pow(2.0,2);
    auto actualValue = zlab::scalarType{4};
    auto tolerance = zlab::evaluateSafeTolerance();
    EXPECT_NEAR(expectedValue, actualValue, tolerance); 
}

TEST(FastPowerFunction, NegativeExponent) {
    auto expectedValue = zlab::pow(2.0,-2);
    auto actualValue = zlab::scalarType{1} / 4;
    auto tolerance = zlab::evaluateSafeTolerance();
    EXPECT_NEAR(expectedValue, actualValue, tolerance); 
}
