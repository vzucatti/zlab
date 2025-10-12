
#include <iostream>

#include"rbf.hpp"

namespace zlab{

scalarType Bump::evaluate(scalarType r) const {
    auto R = this->radius;
    if (r > R) return 0;
    auto ratio = r / R;
    return std::exp(-1 / (1 - zlab::pow(ratio,2)));
}

}
