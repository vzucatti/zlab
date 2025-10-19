
#pragma one

#include <array>

#include "core.hpp"

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


} // end namespace zlab

