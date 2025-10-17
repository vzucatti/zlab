
#pragma once

#include <cassert>
#include <vector>

#ifdef ADD_EIGEN
    #include <eigen3/Eigen/Dense>
#endif

#include "core.hpp"

namespace zlab{

class ZMatrix{
    protected:
        std::vector<scalarType> data;
        positiveIntegerType numberOfRows;
        positiveIntegerType numberOfColumns;
        
        friend class ZVector; 
        
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

class ZVector : public ZMatrix{
    public:
        ZVector(positiveIntegerType length, scalarType fillValue=0) : ZMatrix(length,1, fillValue) {}
        scalarType& operator[](integerType i) { return (*this)(i,0); }
        const scalarType& operator[](integerType i) const { return (*this)(i, 0); }
};

template <typename matrixType>
void axpy(scalarType a, const matrixType& x, matrixType& y){
    assert(x.getNumberOfRows() == y.getNumberOfRows());
    assert(x.getNumberOfColumns() == y.getNumberOfColumns());
    for(auto i=0; i < x.getNumberOfRows(); i++){
        for(auto j=0; j < x.getNumberOfColumns(); j++){
            y(i,j) +=  a * x(i,j);
        }
    }
}

// TODO: write general function that takes numeric types only
void axpy(scalarType, scalarType, scalarType&);

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
