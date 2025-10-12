
#include <iostream>

#include"rbf.hpp"

namespace zlab{

scalarType Bump::evaluate(scalarType r) const {
    auto R = this->radius;
    if (r > R) return 0;
    auto ratio = r / R;
    return std::exp(-1 / (1 - zlab::pow(ratio,2)));
}

scalarType WendlandC0::evaluate(scalarType r) const {
    auto R = this->radius;
    if(r > R) return 0;
    auto ratio = r / R;
    return zlab::pow(1 - ratio, 2);
}

scalarType WendlandC2::evaluate(scalarType r) const {
    auto R = this->radius;
    if(r > R) return 0;
    auto ratio = r / R;
    return zlab::pow(1 - ratio, 4) * (4 * ratio + 1);
}

}
