
#include <type_traits>

#include "gtest/gtest.h"

#include "matrix.hpp"

namespace {
    using zmat = zlab::ZMatrix;
    constexpr bool isNotDefaultConstructible = !std::is_default_constructible<zmat>::value;
    static_assert(isNotDefaultConstructible);
    constexpr bool isNotCopyConstructible = !std::is_copy_constructible<zmat>::value;
    static_assert(isNotCopyConstructible);
}

TEST(ZMatrix, getNumberOfRows){
    zlab::integerType expectedNumberOfRows = 3;
    zlab::integerType numberOfColumns = 5;
    zlab::ZMatrix matrix(expectedNumberOfRows, numberOfColumns);
    auto numberOfRows = matrix.getNumberOfRows();
    ASSERT_EQ(numberOfRows, expectedNumberOfRows);    
}

TEST(ZMatrix, getNumberOfColumns){
    zlab::integerType numberOfRows = 3;
    zlab::integerType expectedNumberOfColumns = 5;
    zlab::ZMatrix matrix(numberOfRows, expectedNumberOfColumns);
    auto numberOfColumns = matrix.getNumberOfColumns();
    ASSERT_EQ(numberOfColumns, expectedNumberOfColumns);    
}

TEST(ZMatrix, get_number_of_elements){
    zlab::integerType expectedNumberOfElements = 12;
    zlab::ZMatrix matrix(3, 4);
    auto numberOfElements = matrix.get_number_of_elements();
    ASSERT_EQ(numberOfElements, expectedNumberOfElements);    
}

TEST(ZVector, length){
    zlab::integerType expectedLength = 5;
    zlab::ZVector vector(5);
    auto actualLength = vector.length();
    ASSERT_EQ(actualLength, expectedLength);    
}

TEST(ZVector, dotProdut){
    zlab::ZVector v1(3,1), v2(3,2);
    auto actualResult = v1.dot(v2);
    zlab::scalarType expectedResult{6};
    auto tolerance = zlab::evaluateSafeTolerance();
    EXPECT_NEAR(actualResult, expectedResult, tolerance); 
}

TEST(ZMatrix, deepCopy){
    zlab::ZMatrix matrix(3,3,2.5);
    auto newMatrix = matrix.copy();
    auto tolerance = zlab::evaluateSafeTolerance();
    for (auto i=0; i < matrix.getNumberOfRows(); i++){
        for (auto j=0; j < matrix.getNumberOfColumns(); j++){
            EXPECT_NEAR(matrix(i,j), newMatrix(i,j), tolerance); 
        }
    }
}

TEST(ZMatrix, axpy){
    zlab::ZMatrix y(2,2,2), x(2,2,2), expectedMatrix(2,2,22);
    zlab::scalarType a{10};
    zlab::axpy(a,x,y);
    auto tolerance = zlab::evaluateSafeTolerance();
    for (auto i=0; i < y.getNumberOfRows(); i++){
        for (auto j=0; j < y.getNumberOfColumns(); j++){
            EXPECT_NEAR(y(i,j), expectedMatrix(i,j), tolerance); 
        }
    }
}

TEST(ZVector, axpy){
    zlab::ZVector y(2,2), x(2,2), expectedVector(2,22);
    zlab::scalarType a{10};
    zlab::axpy(a,x,y);
    auto tolerance = zlab::evaluateSafeTolerance();
    for (auto i=0; i < y.length(); i++){
        EXPECT_NEAR(y[i], expectedVector[i], tolerance); 
    }
}
