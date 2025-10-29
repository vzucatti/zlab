
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

template <typename matrixType, VectorConcept vectorTypeB, VectorConcept vectorTypeX>
void linear_least_squares(
    const matrixType& A,
    const vectorTypeB& b,
    vectorTypeX& x,
    std::optional<scalarType> marginOfError = std::nullopt)
{
    auto [Q, R] = modified_gram_schmidt(A,marginOfError);
    vectorTypeX c(x.size());
    gemv(Q,b,c,1,0,true);
    backward_substitution(R,c,x,marginOfError);
}

template <typename matrixType, VectorConcept vectorTypeB, VectorConcept vectorTypeX>
void linear_solver(
    const matrixType& A,
    const vectorTypeB& b,
    vectorTypeX& x,
    std::optional<scalarType> marginOfError = std::nullopt)
{
    linear_least_squares(A,b,x,marginOfError);
}

template <typename functionTypeF, typename functionTypeDF, VectorConcept vectorType>
auto newton_solver(
    const vectorType& x0,
    const functionTypeF& F,
    const functionTypeDF& dF,
    scalarType tolerance=1e-8,
    integerType iterationLimit = 50)
{
    using matrixType = typename vectorType::matrixType;
    vectorType Fb(x0.size()), dx(x0.size());
    matrixType Jb(x0.size(),x0.size());
    auto xk = x0.copy();
    for(auto i=0; i<iterationLimit; ++i){
        F(xk, Fb);
        scale(Fb,-1); // F = - 1 * F
        if (norm(Fb) < tolerance) break;
        dF(F,xk,Jb);
        linear_solver(Jb,Fb,dx);
        axpy(1.0, dx, xk); // xk = dx + xk
    }
    return xk;
}

} // end zlab namespace
