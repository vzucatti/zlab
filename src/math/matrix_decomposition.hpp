
#pragma once

#include <stdexcept>

#include "utilities.hpp"
#include "core.hpp"

namespace zlab{

template <typename matrixType>
struct ModifiedGramSchmidt {
    matrixType Q;
    matrixType R; 
};

template <typename matrixType>
using MGS = ModifiedGramSchmidt<matrixType>;

template <typename matrixType>
MGS<matrixType> modified_gram_schmidt(const matrixType& data, scalarType tolerance=evaluate_safe_tolerance()){
    auto numberOfRows = data.get_number_of_rows();
    auto numberOfColumns = data.get_number_of_columns();
    matrixType Q(numberOfRows,numberOfColumns), R(numberOfColumns,numberOfColumns);
    auto V = data.copy();
    for(auto j=0; j < numberOfColumns; ++j){
        auto vj = V.column_view(j);
        auto qj = Q.column_view(j);
        R(j,j) = norm(vj);
        if (R(j,j) < tolerance) {
            throw std::runtime_error("MGS: Matrix is ill-conditioned or rank-deficient.");
        }
        axpby(1.0 / R(j,j), vj, 0, qj);
        for(auto k=j+1; k < numberOfColumns; ++k){
            auto vk = V.column_view(k);
            R(j,k) = dot(qj,vk);
            axpy(-R(j,k), qj, vk);
        }
    }
    return {std::move(Q), std::move(R)};
}

} // end namespace zlab
