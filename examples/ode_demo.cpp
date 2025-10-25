
#include <iostream>
#include <cmath>

#include "math.hpp"

int main(){
    using namespace zlab;
    
    auto rhs = [](scalarType t, const ZVector& y, ZVector& f) {
        f[0] = - y[0] - 2 * y[1];
        f[1] =        - 3 * y[1];
    };
    
    ZVector y0(2,1);
    
    integerType numberTimeSteps{100};
    scalarType finalTime{1};
    auto timeStep = finalTime / numberTimeSteps;
    
    auto method = ClassicalRK4;
    auto& numberOfStages = method.numberOfStages;
    RKSolver<numberOfStages, decltype(rhs)> ode1(rhs, y0, timeStep, numberTimeSteps, method);
    auto yn = ode1.solve();
    
    ZVector yExact(2);
    yExact[0] = std::exp(-3*finalTime);
    yExact[1] = std::exp(-3*finalTime);
    
    scalarType error{0};
    for(auto i=0; i<yn.size(); ++i){
        error += std::abs(yn[i] - yExact[i]);
    }
    std::cout << "Error norm: " << error << std::endl;
    
    return 0;
}
