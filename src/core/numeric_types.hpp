
#pragma once

#include <limits>
#include <iostream>

namespace zlab{

using scalarType = double;
using integerType = int;
using positiveIntegerType = std::size_t;

scalarType evaluate_safe_tolerance(scalarType = 1e2);

} // end namespce zlab
