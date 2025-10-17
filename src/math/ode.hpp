
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


} // end namespace zlab

