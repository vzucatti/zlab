
#pragma one

#include <optional>
#include <cmath>

#include "matrix.hpp"

namespace zlab {

template <typename matrixType, VectorConcept vectorTypeB, VectorConcept vectorTypeX>
void backward_substitution(
    const matrixType& A,
    const vectorTypeB& b,
    vectorTypeX& x,
    std::optional<scalarType> marginOfError = std::nullopt)
{
    auto numberOfRows = A.get_number_of_rows();
    assert(numberOfRows == A.get_number_of_columns());
    auto tolerance = evaluate_safe_tolerance(marginOfError);
    for (auto i = 0; i < numberOfRows; ++i) {
        if (std::abs(A(i, i)) < tolerance) {
            throw std::runtime_error("Matrix is singular (zero pivot found).");
        }
    }
    auto i = numberOfRows;
    /* *
     * WARNING: Backward iteration uses the 'do-while' pattern to prevent 
     * an infinite loop.
     * * DANGER: A standard 'for (size_t i = n - 1; i >= 0; --i)' loop 
     * WILL FAIL because 'i' is unsigned and can never be < 0. 
     * When i=0 is decremented, it wraps around to SIZE_MAX.
     * * The 'do-while (i > 0)' check correctly terminates the loop 
     * after the i=0 calculation is performed.
    */
    do {
        --i;
        scalarType sum{0};
        for(auto j=i+1; j < numberOfRows; ++j){
            sum += A(i,j) * x[j];
        }
        x[i] = (b[i] - sum) / A(i,i);
    } while (i >0);
}

} // end zlab namespace
