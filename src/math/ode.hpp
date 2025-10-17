
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

} // end namespace zlab

