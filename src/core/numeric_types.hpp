
#pragma once

#include <optional>

namespace zlab{

using scalarType = double;
using integerType = int;
using positiveIntegerType = std::size_t;

scalarType evaluate_safe_tolerance(std::optional<scalarType> marginOfErrorOption = std::nullopt);

} // end namespce zlab
