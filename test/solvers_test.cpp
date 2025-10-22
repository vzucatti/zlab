
#include "gtest/gtest.h"

#include "core.hpp"
#include "math.hpp"

TEST(Solver, BackwardSubstitution){
    zlab::ZMatrix A(3,3);
    A(0,0) = 2; A(0,1) = -1; A(0,2) = 3;
    A(1,1) = 4; A(1,2) = 1;
    A(2,2) = 5;
    zlab::ZVector b(3), x(3);
    b[0] = 9; b[1] = 11; b[2] = 15;
    zlab::backward_substitution(A,b,x);
    auto tolerance = zlab::evaluate_safe_tolerance();
    for(auto i=0; i<b.size(); ++i){
        EXPECT_NEAR(x[i], i+1, tolerance);
    }
}
