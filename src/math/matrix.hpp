
#pragma once

#include <cassert>
#include <vector>
#include <span>

#ifdef ADD_EIGEN
    #include <eigen3/Eigen/Dense>
#endif

#include "core.hpp"

namespace zlab{

class ColumnView;

class ZMatrix{
    private:
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
        
        void fill(scalarType);
        
        scalarType& operator()(integerType, integerType);
        const scalarType& operator()(integerType, integerType) const;
        
        std::span<const scalarType> row_view(integerType) const;
        ColumnView column_view(integerType) const;

        positiveIntegerType getNumberOfRows() const { return numberOfRows; }
        positiveIntegerType getNumberOfColumns() const { return numberOfColumns; }
        positiveIntegerType get_number_of_elements() const;
        
        void print() const;
};

class ColumnView {
    private:
        const ZMatrix& matrix;
        positiveIntegerType columnIndex;
    public:
        ColumnView(const ZMatrix&, integerType);

        positiveIntegerType size() const { return matrix.getNumberOfRows(); }
        
        const scalarType& operator[](integerType) const;
};

class ZVector {
    private:
        ZMatrix matrix;
    public:
        ZVector() = delete;
        ZVector(const ZVector&) = delete;
        ZVector(ZVector&&);
        ZVector(integerType, scalarType=0);
        virtual ~ZVector() = default;
        ZVector& operator=(const ZVector&);
        ZVector& operator=(ZVector&&);
        
        ZVector copy() const;
        
        void fill(scalarType);

        ZVector& operator=(std::span<const scalarType>);
        ZVector& operator=(const ColumnView&);

        scalarType& operator[](integerType i) { return matrix(i,0); }
        const scalarType& operator[](integerType i) const { return matrix(i, 0); }

        positiveIntegerType length() const{ return matrix.getNumberOfRows(); }
        
        scalarType dot(const ZVector&) const;
        scalarType norm(scalarType=2) const;

        void print() const { matrix.print(); };
};

template <typename vectorType>
void axpy(scalarType a, const vectorType& x, vectorType& y){
    assert(x.length() == y.length());
    for(auto i=0; i < x.length(); i++){
        y[i] +=  a * x[i];
    }
}

template <typename matrixType>
void gemm(
    const matrixType& A, 
    const matrixType& B, 
    matrixType& C, 
    scalarType a=1,
    scalarType b=1)
{
    assert(C.getNumberOfRows() == A.getNumberOfRows());
    assert(A.getNumberOfColumns() == B.getNumberOfRows());
    assert(C.getNumberOfColumns() == B.getNumberOfColumns());
    for(auto i=0; i<A.getNumberOfRows(); ++i){
        for(auto k=0; k<C.getNumberOfColumns(); ++k){
            auto sum = b * C(i, k);
            for(auto j=0; j<B.getNumberOfRows(); ++j){
               sum += a * A(i,j) * B(j,k);
            }
            C(i, k) = sum;
        }
    }
}

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
