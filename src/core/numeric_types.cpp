
#include <limits>
#include <optional>

#include "numeric_types.hpp"

namespace zlab{

scalarType evaluate_safe_tolerance(std::optional<scalarType> marginOfErrorOption){
    auto eps = std::numeric_limits<scalarType>::epsilon();
    auto defaultMarginOfError = 1e2;
    auto marginOfError = marginOfErrorOption.value_or(defaultMarginOfError);
    return eps * marginOfError;
}

}
