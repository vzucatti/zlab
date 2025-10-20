
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

class ZVector : public ZMatrix{
    public:
        ZVector(positiveIntegerType length, scalarType fillValue=0) : ZMatrix(length,1, fillValue) {}
        
        ZVector copy() const;
        
        ZVector& operator=(std::span<const scalarType>);
        ZVector& operator=(const ColumnView&);
            
        scalarType& operator[](integerType i) { return (*this)(i,0); }
        const scalarType& operator[](integerType i) const { return (*this)(i, 0); }
        
        positiveIntegerType length() const{ return (*this).get_number_of_elements(); }
        
        scalarType dot(const ZVector&) const;
        scalarType norm(scalarType=2) const;
};

template <typename matrixType>
void fill(matrixType& matrix, scalarType fillValue){
    for(auto i=0; i < matrix.getNumberOfRows(); i++){
        for(auto j=0; j < matrix.getNumberOfColumns(); j++){
            matrix(i,j) = fillValue;
        }
    }
}

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
