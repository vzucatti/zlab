
#pragma one

#include <array>

#include "core.hpp"

namespace zlab{

template <positiveIntegerType numberOfStages>
struct ButcherTableau {
    std::array<std::array<scalarType, numberOfStages>, numberOfStages> A;
    std::array<scalarType, numberOfStages> b;
    std::array<scalarType, numberOfStages> c;
};

static constexpr ButcherTableau<1> ButcherTableauExplicitEuler = {{{{0.0}}}, {1.0}, {0.0}};
static constexpr auto& ExplicitEuler = ButcherTableauExplicitEuler;

static constexpr ButcherTableau<2> ButcherTableauRungeKutta2 = {
    {
    {{0.0, 0.0},
    {0.5, 0.0}}
    },
    {0.0, 1.0},
    {0.0, 0.5}
};
static constexpr auto& RK2 = ButcherTableauRungeKutta2;

static constexpr ButcherTableau<4> ButcherTableauRungeKutta4 = {
    {{
        {0.0, 0.0, 0.0, 0.0},
        {0.5, 0.0, 0.0, 0.0},
        {0.0, 0.5, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0}
    }},
    {1.0/6.0, 2.0/6.0, 2.0/6.0, 1.0/6.0},
    {0.0, 0.5, 0.5, 1.0}
};
static constexpr auto& RK4 = ButcherTableauRungeKutta4;

} // end namespace zlab

