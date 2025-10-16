
#pragma once

#include <cassert>
#include <vector>

#ifdef ADD_EIGEN
    #include <eigen3/Eigen/Dense>
#endif

#include "core.hpp"

namespace zlab{

class ZMatrix{
        std::vector<scalarType> data;
        positiveIntegerType numberOfRows;
        positiveIntegerType numberOfColumns;
        
        positiveIntegerType computeVectorIndex(integerType, integerType) const;
    public:
        ZMatrix() = delete;
        ZMatrix(const ZMatrix&) = delete;
        ZMatrix(ZMatrix&&);
        ZMatrix(integerType, integerType, scalarType=0);
        virtual ~ZMatrix() = default;
        ZMatrix& operator=(const ZMatrix&);
        ZMatrix& operator=(ZMatrix&&);
        
        ZMatrix copy() const;
        
        scalarType& operator()(integerType, integerType);
        const scalarType& operator()(integerType, integerType) const;

        positiveIntegerType getNumberOfRows() const { return numberOfRows; }
        positiveIntegerType getNumberOfColumns() const { return numberOfColumns; }
        
        void print() const;
};

#ifdef ADD_EIGEN

class EigenMatrix{
        Eigen::Matrix<scalarType, Eigen::Dynamic, Eigen::Dynamic> matrix;
    public:
        EigenMatrix() = delete;
        EigenMatrix(const EigenMatrix&) = delete;
        EigenMatrix(integerType, integerType, scalarType=0);
        
        void print() const { std::cout << matrix << std::endl; }
};

EigenMatrix::EigenMatrix(
    integerType numberOfRows,
    integerType numberOfColumns,
    scalarType fillValue) : 
    matrix(numberOfRows, numberOfColumns) {
    assert(numberOfRows > 0 && numberOfColumns > 0);
    matrix.setConstant(fillValue);
}

#endif

template <typename matrixType>
class Matrix{
        matrixType matrix;
    public:
        Matrix(integerType, integerType, scalarType=0);
        
        void print() const { matrix.print(); }
};

template <typename matrixType>
Matrix<matrixType>::Matrix(
    integerType numberOfRows, 
    integerType numberOfColumns,
    scalarType fillValue) : 
    matrix(numberOfRows, numberOfColumns, fillValue){
    assert(numberOfRows > 0 && numberOfColumns > 0);
}

} // end namespace zlab
