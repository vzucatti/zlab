
#include "numeric_types.hpp"

namespace zlab{

scalarType evaluateSafeTolerance(scalarType marginOfError){
    auto eps = std::numeric_limits<scalarType>::epsilon();
    return eps * marginOfError;
}

}
