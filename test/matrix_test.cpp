
#include "gtest/gtest.h"

#include "matrix.hpp"

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
