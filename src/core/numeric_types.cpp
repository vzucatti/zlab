
#include "numeric_types.hpp"

namespace zlab{

scalarType evaluate_safe_tolerance(scalarType marginOfError){
    auto eps = std::numeric_limits<scalarType>::epsilon();
    return eps * marginOfError;
}

}
