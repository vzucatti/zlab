
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

TEST(ZMatrix, get_number_of_rows){
    zlab::integerType expectedNumberOfRows = 3;
    zlab::integerType numberOfColumns = 5;
    zlab::ZMatrix matrix(expectedNumberOfRows, numberOfColumns);
    auto numberOfRows = matrix.get_number_of_rows();
    ASSERT_EQ(numberOfRows, expectedNumberOfRows);    
}

TEST(ZMatrix, get_number_of_columns){
    zlab::integerType numberOfRows = 3;
    zlab::integerType expectedNumberOfColumns = 5;
    zlab::ZMatrix matrix(numberOfRows, expectedNumberOfColumns);
    auto numberOfColumns = matrix.get_number_of_columns();
    ASSERT_EQ(numberOfColumns, expectedNumberOfColumns);    
}

TEST(ZMatrix, get_number_of_elements){
    zlab::integerType expectedNumberOfElements = 12;
    zlab::ZMatrix matrix(3, 4);
    auto numberOfElements = matrix.get_number_of_elements();
    ASSERT_EQ(numberOfElements, expectedNumberOfElements);    
}

TEST(ZVector, size){
    zlab::integerType expectedsize = 5;
    zlab::ZVector vector(5);
    auto actualsize = vector.size();
    ASSERT_EQ(actualsize, expectedsize);    
}

TEST(ZVector, dotProdut){
    zlab::ZVector v1(3,1), v2(3,2);
    auto actualResult = dot(v1,v2);
    zlab::scalarType expectedResult{6};
    auto tolerance = zlab::evaluate_safe_tolerance();
    EXPECT_NEAR(actualResult, expectedResult, tolerance); 
}

TEST(ZVector, copyMatrixRowView){
    zlab::ZMatrix matrix(3,3,1);
    for(auto i=0; i < matrix.get_number_of_rows(); ++i){
        for (auto j=0; j < matrix.get_number_of_columns(); j++){
            matrix(i,j) = 10*i + j;
        }
    }
    zlab::ZVector vector(3);
    vector = matrix.row_view(0);
    auto tolerance = zlab::evaluate_safe_tolerance();
    for (auto i=0; i < vector.size(); ++i){
        auto expectedResult = i;
        auto actualResult = vector[i];
        EXPECT_NEAR(actualResult, expectedResult, tolerance); 
    }
}

TEST(ZVector, copyMatrixColumnView){
    zlab::ZMatrix matrix(3,3,1);
    for(auto i=0; i < matrix.get_number_of_rows(); ++i){
        for (auto j=0; j < matrix.get_number_of_columns(); j++){
            matrix(i,j) = 10*i + j;
        }
    }
    zlab::ZVector vector(3);
    vector = matrix.column_view(0);
    auto tolerance = zlab::evaluate_safe_tolerance();
    for (auto i=0; i < vector.size(); ++i){
        auto expectedResult = 10*i;
        auto actualResult = vector[i];
        EXPECT_NEAR(actualResult, expectedResult, tolerance); 
    }
}

TEST(ZVector, L1_norm){
    zlab::ZVector v(3);
    for (auto i=0; i<v.size();++i) v[i] = i+1;
    v.print();    
    auto actualNorm = norm(v,1);
    zlab::scalarType expectedNorm{6};
    auto tolerance = zlab::evaluate_safe_tolerance();
    EXPECT_NEAR(actualNorm, expectedNorm, tolerance); 
}

TEST(ZVector, L2_norm){
    zlab::ZVector v(3);
    for (auto i=0; i<v.size();++i) v[i] = i+1;
    v.print();    
    auto actualNorm = norm(v,2);
    zlab::scalarType expectedNorm{std::sqrt(14)};
    auto tolerance = zlab::evaluate_safe_tolerance();
    EXPECT_NEAR(actualNorm, expectedNorm, tolerance); 
}

TEST(ZVector, L3_norm){
    zlab::ZVector v(3);
    for (auto i=0; i<v.size();++i) v[i] = i+1;
    v.print();    
    auto actualNorm = norm(v,3);
    zlab::scalarType expectedNorm{std::pow(6, 2.0/3.0)};
    auto tolerance = zlab::evaluate_safe_tolerance();
    EXPECT_NEAR(actualNorm, expectedNorm, tolerance); 
}

TEST(ZVector, L4_norm){
    zlab::ZVector v(3);
    for (auto i=0; i<v.size();++i) v[i] = i+1;
    v.print();    
    auto actualNorm = norm(v,4);
    zlab::scalarType expectedNorm{std::pow(2, 0.25) * std::sqrt(7)};
    auto tolerance = zlab::evaluate_safe_tolerance();
    EXPECT_NEAR(actualNorm, expectedNorm, tolerance); 
}

TEST(ZVector, Linf_norm){
    zlab::ZVector v(3);
    for (auto i=0; i<v.size();++i) v[i] = i+1;
    v.print();
    auto infinity = std::numeric_limits<zlab::scalarType>::infinity();
    auto actualNorm = norm(v,infinity);
    zlab::scalarType expectedNorm{3};
    auto tolerance = zlab::evaluate_safe_tolerance();
    EXPECT_NEAR(actualNorm, expectedNorm, tolerance); 
}

TEST(ZMatrix, deepCopy){
    zlab::ZMatrix matrix(3,3,2.5);
    auto newMatrix = matrix.copy();
    auto tolerance = zlab::evaluate_safe_tolerance();
    for (auto i=0; i < matrix.get_number_of_rows(); i++){
        for (auto j=0; j < matrix.get_number_of_columns(); j++){
            EXPECT_NEAR(matrix(i,j), newMatrix(i,j), tolerance); 
        }
    }
}

TEST(ZMatrix, fill){
    zlab::ZMatrix matrix(3,4);
    zlab::scalarType fillValue = 3;
    matrix.fill(fillValue);
    auto tolerance = zlab::evaluate_safe_tolerance();
    for (auto i=0; i < matrix.get_number_of_rows(); i++){
        for (auto j=0; j < matrix.get_number_of_columns(); j++){
            EXPECT_NEAR(matrix(i,j), fillValue, tolerance); 
        }
    }
}

TEST(ZMatrix, gemm){
    zlab::ZMatrix A(3,4), B(4,2), C(3,2,1), R(3,2);
    for (auto i=0; i<A.get_number_of_rows(); ++i){
        for (auto j=0; j<A.get_number_of_columns(); ++j){
            A(i,j) = i+1;
        }
    }
    B(0, 0) = 1; B(0, 1) = 2;
    B(1, 0) = 1; B(1, 1) = 2;
    B(2, 0) = 1; B(2, 1) = 2;
    B(3, 0) = 1; B(3, 1) = 2;
    zlab::gemm(A,B,C,2,3);
    R(0, 0) = 11; R(0, 1) = 19;
    R(1, 0) = 19; R(1, 1) = 35;
    R(2, 0) = 27; R(2, 1) = 51;
    auto tolerance = zlab::evaluate_safe_tolerance();
    for (auto i=0; i < R.get_number_of_rows(); i++){
        for (auto j=0; j < R.get_number_of_columns(); j++){
            EXPECT_NEAR(C(i,j), R(i,j), tolerance); 
        }
    }
}

TEST(ZVector, fill){
    zlab::ZVector vector(3);
    zlab::scalarType fillValue = 3;
    vector.fill(fillValue);
    auto tolerance = zlab::evaluate_safe_tolerance();
    for (auto i=0; i < vector.size(); i++){
        EXPECT_NEAR(vector[i], fillValue, tolerance); 
    }
}

TEST(ZVector, scale){
    zlab::ZVector v(3,1);
    zlab::scalarType expectedValue{2};
    zlab::scale(v,expectedValue);
    auto tolerance = zlab::evaluate_safe_tolerance();
    for (auto i=0; i < v.size(); i++){
        EXPECT_NEAR(v[i], expectedValue, tolerance); 
    }
}

TEST(ZVector, axpy){
    zlab::ZVector y(2,2), x(2,2), expectedVector(2,22);
    zlab::scalarType a{10};
    zlab::axpy(a,x,y);
    auto tolerance = zlab::evaluate_safe_tolerance();
    for (auto i=0; i < y.size(); i++){
        EXPECT_NEAR(y[i], expectedVector[i], tolerance); 
    }
}

TEST(ZVector, aypx){
    zlab::ZVector y(3,2), x(3,6);
    zlab::scalarType expectedValue{10};
    zlab::aypx(2,y,x);
    auto tolerance = zlab::evaluate_safe_tolerance();
    for (auto i=0; i < y.size(); i++){
        EXPECT_NEAR(y[i], expectedValue, tolerance); 
    }
}

TEST(ZVector, axpby){
    zlab::ZVector y(3,2), x(3,6);
    zlab::scalarType expectedValue{18};
    zlab::axpby(2,x,3,y);
    auto tolerance = zlab::evaluate_safe_tolerance();
    for (auto i=0; i < y.size(); i++){
        EXPECT_NEAR(y[i], expectedValue, tolerance); 
    }
}
