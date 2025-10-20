
#include <type_traits>
#include <limits>
#include <cmath>

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

TEST(ZVector, copyMatrixRowView){
    using namespace zlab;
    ZMatrix matrix(3,3,1);
    for(auto i=0; i < matrix.getNumberOfRows(); ++i){
        for (auto j=0; j < matrix.getNumberOfColumns(); j++){
            matrix(i,j) = 10*i + j;
        }
    }
    ZVector vector(3);
    vector = matrix.row_view(0);
    auto tolerance = zlab::evaluateSafeTolerance();
    for (auto i=0; i < vector.length(); ++i){
        auto expectedResult = i;
        auto actualResult = vector[i];
        EXPECT_NEAR(actualResult, expectedResult, tolerance); 
    }
}

TEST(ZVector, L1_norm){
    using namespace zlab;
    ZVector v(3);
    for (auto i=0; i<v.length();++i) v[i] = i+1;
    v.print();    
    auto actualNorm = v.norm(1);
    scalarType expectedNorm{6};
    auto tolerance = evaluateSafeTolerance();
    EXPECT_NEAR(actualNorm, expectedNorm, tolerance); 
}

TEST(ZVector, L2_norm){
    using namespace zlab;
    ZVector v(3);
    for (auto i=0; i<v.length();++i) v[i] = i+1;
    v.print();    
    auto actualNorm = v.norm(2);
    scalarType expectedNorm{std::sqrt(14)};
    auto tolerance = evaluateSafeTolerance();
    EXPECT_NEAR(actualNorm, expectedNorm, tolerance); 
}

TEST(ZVector, L3_norm){
    using namespace zlab;
    ZVector v(3);
    for (auto i=0; i<v.length();++i) v[i] = i+1;
    v.print();    
    auto actualNorm = v.norm(3);
    scalarType expectedNorm{std::pow(6, 2.0/3.0)};
    auto tolerance = evaluateSafeTolerance();
    EXPECT_NEAR(actualNorm, expectedNorm, tolerance); 
}

TEST(ZVector, L4_norm){
    using namespace zlab;
    ZVector v(3);
    for (auto i=0; i<v.length();++i) v[i] = i+1;
    v.print();    
    auto actualNorm = v.norm(4);
    scalarType expectedNorm{std::pow(2, 0.25) * std::sqrt(7)};
    auto tolerance = evaluateSafeTolerance();
    EXPECT_NEAR(actualNorm, expectedNorm, tolerance); 
}

TEST(ZVector, Linf_norm){
    using namespace zlab;
    ZVector v(3);
    for (auto i=0; i<v.length();++i) v[i] = i+1;
    v.print();
    auto infinity = std::numeric_limits<scalarType>::infinity();
    auto actualNorm = v.norm(infinity);
    scalarType expectedNorm{3};
    auto tolerance = evaluateSafeTolerance();
    EXPECT_NEAR(actualNorm, expectedNorm, tolerance); 
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

TEST(ZMatrix, fill){
    zlab::ZMatrix matrix(3,4);
    zlab::scalarType fillValue = 3;
    zlab::fill(matrix, fillValue);
    auto tolerance = zlab::evaluateSafeTolerance();
    for (auto i=0; i < matrix.getNumberOfRows(); i++){
        for (auto j=0; j < matrix.getNumberOfColumns(); j++){
            EXPECT_NEAR(matrix(i,j), fillValue, tolerance); 
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
