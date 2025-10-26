
#pragma once

#include<cmath>
#include<concepts>
#include<type_traits>

#include "core.hpp"

namespace zlab{

// NUMERIC CONCEPT
// This concept enforces that a type T must be either a standard integral 
// or floating-point type.
template <typename T>
concept NumericConcept = std::floating_point<T> || std::integral<T>;

// POW OVERLOAD 1: General Power (Floating-Point Exponent)
// This uses the standard library's pow function.
template <NumericConcept T, NumericConcept U>
auto pow(T a, U b) {
    return std::pow(a, b);
}

// POW OVERLOAD 2: Optimized Power (Integer Exponent)
// This overload will now be correctly selected ONLY when the exponent is an integer.
//
// ALGORITHM: Exponentiation by Squaring
// This method calculates a^n (for integer n) in O(log n) time. It avoids n linear
// multiplications by halving the exponent (m /= 2) and checking if m is odd (m % 2 == 1).
template<NumericConcept T, std::integral I>
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

