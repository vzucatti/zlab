
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
        ZVector(positiveIntegerType length, scalarType fillValue=0) : matrix(length,1, fillValue) {}
        
        ZVector copy() const;

        ZVector& operator=(std::span<const scalarType>);
        ZVector& operator=(const ColumnView&);

        scalarType& operator[](integerType i) { return matrix(i,0); }
        const scalarType& operator[](integerType i) const { return matrix(i, 0); }

        positiveIntegerType length() const{ return matrix.getNumberOfRows(); }
        
        scalarType dot(const ZVector&) const;
        scalarType norm(scalarType=2) const;

        void print() const { matrix.print(); };
};

inline void fill(ZVector& v, scalarType fillValue) {
    for (size_t i = 0; i < v.length(); ++i) {
        v[i] = fillValue;
    }
}

template <typename vectorType>
inline void axpy(scalarType a, const vectorType& x, vectorType& y){
    assert(x.length() == y.length());
    for(auto i=0; i < x.length(); i++){
        y[i] +=  a * x[i];
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
