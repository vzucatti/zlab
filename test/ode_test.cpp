
#include "gtest/gtest.h"

#include "core.hpp"
#include "math.hpp"

TEST(ODE, OrderOfConvergenceClassicalRK4){
    using namespace zlab;
    auto method = ClassicalRK4;
    auto& numberOfStages = method.numberOfStages;
    
    auto f1 = [](scalarType /*t*/, const ZVector& y, ZVector& f) {
        fill(f,0);
        axpy(-1,y,f);
    };
    
    ZVector y0(1,1);
    
    integerType numberTimeSteps1{10};
    scalarType timeStep1 = scalarType{1} / numberTimeSteps1;
    RKSolver<numberOfStages, decltype(f1)> ode1(f1, y0, timeStep1, numberTimeSteps1, method);
    auto yn1 = ode1.solve();
    auto error1 = std::abs(yn1[0] - std::exp(-1));
    
    integerType numberTimeSteps2{20};
    scalarType timeStep2 = scalarType{1} / numberTimeSteps2;
    RKSolver<numberOfStages, decltype(f1)> ode2(f1, y0, timeStep2, numberTimeSteps2, method);
    auto yn2 = ode2.solve();
    auto error2 = std::abs(yn2[0] - std::exp(-1));
    
    auto slope = (std::log(error1) - std::log(error2)) / (std::log(timeStep1) - std::log(timeStep2));
    scalarType expectedSlope{numberOfStages};
    scalarType tolerance{1e-1};
    
    EXPECT_NEAR(slope, expectedSlope, tolerance); 
}

