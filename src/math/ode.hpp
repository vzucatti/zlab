
#pragma one

#include <functional>
#include <cassert>
#include <vector>
#include <array>

#include "core.hpp"
#include "matrix.hpp"

namespace zlab{

template <positiveIntegerType numberOfStages_>
struct ButcherTableau {
    static constexpr auto numberOfStages = numberOfStages_;
    std::array<std::array<scalarType, numberOfStages_>, numberOfStages_> A;
    std::array<scalarType, numberOfStages_> b;
    std::array<scalarType, numberOfStages_> c;
};

static constexpr ButcherTableau<1> ButcherTableauExplicitEuler = {{{{0.0}}}, {1.0}, {0.0}};
static constexpr auto& ExplicitEuler = ButcherTableauExplicitEuler;

static constexpr ButcherTableau<2> ButcherTableauMidpointMethod = {
    {{
    {0.0, 0.0},
    {0.5, 0.0}
    }},
    {0.0, 1.0},
    {0.0, 0.5}
};
static constexpr auto& MidpointMethod = ButcherTableauMidpointMethod;

static constexpr ButcherTableau<2> ButcherTableauHeunsMethod2 = {
    {{
    {0.0, 0.0},
    {1.0, 0.0}
    }},
    {0.5, 0.5},
    {0.0, 1.0}
};
static constexpr auto& HeunsMethod2 = ButcherTableauHeunsMethod2;

static constexpr ButcherTableau<2> ButcherTableauRalstonsMethod2 = {
    {{
    {0.0, 0.0},
    {2.0/3.0, 0.0}
    }},
    {1.0/4.0, 3./4.0},
    {0.0, 2./3.0}
};
static constexpr auto& RalstonsMethod2 = ButcherTableauRalstonsMethod2;

static constexpr ButcherTableau<3> ButcherTableauHeunsMethod3 = {
    {{
    {0.0, 0.0, 0.0},
    {1.0/3.0, 0.0, 0.0},
    {0.0, 2.0/3.0, 0.0}
    }},
    {0.25, 0.0, 0.75},
    {0.0, 1.0/3.0, 2.0/3.0}
};
static constexpr auto& HeunsMethod3 = ButcherTableauHeunsMethod3;

static constexpr ButcherTableau<3> ButcherTableauRalstonsMethod3 = {
    {{
    {0.0, 0.0, 0.0},
    {0.5, 0.0, 0.0},
    {0.0, 0.75, 0.0}
    }},
    {2.0/9.0, 1./3.0, 4.0/9.0},
    {0.0, 0.5, 0.75}
};
static constexpr auto& RalstonsMethod3 = ButcherTableauRalstonsMethod3;

static constexpr ButcherTableau<3> StrongStabilityPreservingRungeKutta3 = {
    {{
    {0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.25, 0.25, 0.0}
    }},
    {1.0/6.0, 1./6.0, 2.0/3.0},
    {0.0, 1.0, 0.5}
};
static constexpr auto& SSPRK3 = StrongStabilityPreservingRungeKutta3;

static constexpr ButcherTableau<4> ButcherTableauClassicalRungeKutta4 = {
    {{
    {0.0, 0.0, 0.0, 0.0},
    {0.5, 0.0, 0.0, 0.0},
    {0.0, 0.5, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0}
    }},
    {1.0/6.0, 2.0/6.0, 2.0/6.0, 1.0/6.0},
    {0.0, 0.5, 0.5, 1.0}
};
static constexpr auto& ClassicalRK4 = ButcherTableauClassicalRungeKutta4;

template<positiveIntegerType numberOfStages, typename functionType>
class RungeKuttaSolver{
        functionType F;
        scalarType timeStep;
        positiveIntegerType numberTimeSteps;
        ZVector initialState;
        const ButcherTableau<numberOfStages>& butcherTableau;
    public:
        RungeKuttaSolver() = delete;
        RungeKuttaSolver(const functionType&, 
                         const ZVector&, 
                         const scalarType,
                         const integerType,
                         const ButcherTableau<numberOfStages>&);
        
        auto solve(std::function<void(integerType, const ZVector&)> = [](integerType, const ZVector&){});
        
        auto allocate_stage_buffers();
};

template<positiveIntegerType numberOfStages, typename functionType>
RungeKuttaSolver<numberOfStages, functionType>::RungeKuttaSolver(
    const functionType& F,
    const ZVector& initialState,
    const scalarType timeStep,
    const integerType numberTimeSteps,
    const ButcherTableau<numberOfStages>& butcherTableau) : 
    F(std::move(F)), 
    initialState(initialState.copy()),
    timeStep(timeStep), 
    numberTimeSteps(numberTimeSteps),
    butcherTableau(butcherTableau) {
    assert(timeStep > 0);
    assert(numberTimeSteps > 0);
}

template <positiveIntegerType numberOfStages, typename functionType>
auto RungeKuttaSolver<numberOfStages, functionType>::solve(std::function<void(integerType, const ZVector&)> callback){
    scalarType presentTime{0};
    
    auto bufferState = initialState.copy();
    auto futureState = initialState.copy();
    auto presentState = initialState.copy();
    auto bufferFunction = initialState.copy();
    
    const auto& [A, b, c] = butcherTableau;
    
    auto K = allocate_stage_buffers();

    auto safeZero = evaluate_safe_tolerance();
      
    for (auto it=0; it < numberTimeSteps; it++){
        for(auto s=0; s < numberOfStages; s++){
            bufferState = presentState;
            for(auto j=0; j < numberOfStages; j++){
                if(A[s][j] > safeZero) {
                    axpy(A[s][j] * timeStep, K[j], bufferState);
                }
            }
            F(presentTime + c[s] * timeStep, bufferState, bufferFunction);
            K[s] = bufferFunction;
            axpy(timeStep * b[s], K[s], futureState);
        }
        presentTime += timeStep;
        presentState = futureState;
        
        callback(it, presentState);
    }
    return presentState;
}

template <positiveIntegerType numberOfStages, typename functionType>
using RKSolver = RungeKuttaSolver<numberOfStages, functionType>;

template <positiveIntegerType numberOfStages, typename functionType>
auto RungeKuttaSolver<numberOfStages, functionType>::allocate_stage_buffers(){
    std::vector<ZVector> K;
    K.reserve(numberOfStages);
    for(auto s=0; s < numberOfStages; s++) {
        K.emplace_back(initialState.length());
    }
    return K;
}

} // end namespace zlab

