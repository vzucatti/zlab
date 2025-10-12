
#include "gtest/gtest.h"

#include "core.hpp"
#include "math.hpp"

TEST(BumpRBF, Center) {
    using scalarType=zlab::scalarType;
    auto radius = scalarType{1};
    zlab::Bump rbf{radius};
    auto evaluationDistance = scalarType{0};
    auto rbfActualValue = rbf.evaluate(evaluationDistance);
    auto rbfExpectedValue = std::exp(-1); // TODO: explain why this value is expected
    auto tolerance = zlab::evaluateSafeTolerance();
    EXPECT_NEAR(rbfExpectedValue, rbfActualValue, tolerance);
}

// TODO: add interior test

TEST(BumpRBF, OutsideSupport) {
    using scalarType=zlab::scalarType;
    auto radius = scalarType{1};
    zlab::Bump rbf{radius};
    auto evaluationDistance = scalarType{1.05};
    auto rbfActualValue = rbf.evaluate(evaluationDistance);
    auto rbfExpectedValue = scalarType{0};
    auto tolerance = zlab::evaluateSafeTolerance();
    EXPECT_NEAR(rbfExpectedValue, rbfActualValue, tolerance); 
}


