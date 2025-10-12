
#pragma once

#include<cmath>
#include<type_traits>

#include "core.hpp"

//TODO: write benchmark
//TODO: write tests: check for negative and positive

namespace zlab{

template<class T,
         class U,
         std::enable_if_t<!std::is_integral_v<std::decay_t<U>>, int> = 0>
auto pow(T a, U b) { return std::pow(a, b); }

template<class T,
         class I,
         std::enable_if_t<std::is_integral_v<std::decay_t<I>>, int> = 0>
auto pow(T a, I n) {
    using R = scalarType;
    R base{a};
    if (n == 0) return R{1};
        I m = std::abs(n);
        R res{1};
        // Exponentiation by squaring
        while (m > 0) {
            if (m % 2 == 1) res *= base;
            base *= base;
            m /= 2;
        }
        return n > 0 ? res : (R{1} / res);
}

}

