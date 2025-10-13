
#pragma once

#include <limits>
#include <iostream>

namespace zlab{

using scalarType = double;
using integerType = int;
using positiveIntegerType = std::size_t;

scalarType evaluateSafeTolerance(scalarType = 1e2);

} // end namespce zlab
