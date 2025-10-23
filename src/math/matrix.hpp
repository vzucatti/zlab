
#pragma once

#include <stdexcept>
#include <concepts>
#include <cassert>
#include <limits>
#include <vector>
#include <span>

#ifdef ADD_EIGEN
    #include <eigen3/Eigen/Dense>
#endif

#include "utilities.hpp"
#include "core.hpp"

namespace zlab{

class ColumnView;

class ZMatrix{
    private:
        std::vector<scalarType> data;
        positiveIntegerType numberOfRows;
        positiveIntegerType numberOfColumns;
        
        positiveIntegerType compute_vector_index(integerType, integerType) const;
    public:
        ZMatrix() = delete;
        ZMatrix(const ZMatrix&) = delete;
        ZMatrix(ZMatrix&&) noexcept;
        ZMatrix(integerType, integerType, scalarType=0);
        virtual ~ZMatrix() = default;
        ZMatrix& operator=(const ZMatrix&);
        ZMatrix& operator=(ZMatrix&&) noexcept;
        
        ZMatrix copy() const;
        
        void fill(scalarType);
        
        scalarType& operator()(integerType, integerType);
        const scalarType& operator()(integerType, integerType) const;
        
        std::span<scalarType> row_view(integerType);
        ColumnView column_view(integerType);

        positiveIntegerType get_number_of_rows() const { return numberOfRows; }
        positiveIntegerType get_number_of_columns() const { return numberOfColumns; }
        positiveIntegerType get_number_of_elements() const;
        
        void print() const;
};

class ColumnView {
    private:
        ZMatrix& matrix;
        positiveIntegerType columnIndex;
    public:
        ColumnView(ZMatrix&, integerType);
        scalarType& operator[](integerType);
        const scalarType& operator[](integerType) const;
        positiveIntegerType size() const { return matrix.get_number_of_rows(); }
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

        ZVector& operator=(const std::span<scalarType>);
        ZVector& operator=(const ColumnView&);

        scalarType& operator[](integerType i) { return matrix(i,0); }
        const scalarType& operator[](integerType i) const { return matrix(i, 0); }

        positiveIntegerType size() const{ return matrix.get_number_of_rows(); }
        
        void print() const { matrix.print(); };
};

template <typename vectorType>
concept VectorConcept = requires(const vectorType v, positiveIntegerType i) {
    v.size();
    v[i];
};

template <VectorConcept vectorTypeX, VectorConcept vectorTypeY>
void axpy(scalarType a, const vectorTypeX& x, vectorTypeY& y){
    assert(x.size() == y.size());
    for(auto i=0; i < x.size(); i++){
        y[i] +=  a * x[i];
    }
}

template <VectorConcept vectorTypeX, VectorConcept vectorTypeY>
void axpby(scalarType a, const vectorTypeX& x, scalarType b, vectorTypeY& y){
    assert(x.size() == y.size());
    for(auto i=0; i < x.size(); i++){
        y[i] =  a * x[i] + b * y[i];
    }
}

template <VectorConcept vectorTypeX, VectorConcept vectorTypeY>
void aypx(scalarType a, vectorTypeX& y, const vectorTypeY& x){
    assert(x.size() == y.size());
    for(auto i=0; i < x.size(); i++){
        y[i] = a * y[i] + x[i];
    }
}

template <VectorConcept vectorType>
void scale(vectorType& v, scalarType a){
    for(auto i=0; i < v.size(); i++){
        v[i] *=  a;
    }
}

template <VectorConcept vectorType>
scalarType norm(vectorType&v, scalarType p=2) {
    if (p == std::numeric_limits<scalarType>::infinity()) {
        scalarType max_abs = 0.0;
        for (auto i=0; i < v.size(); ++i){
            max_abs = std::max(max_abs, std::abs(v[i]));
        }
        return max_abs;
    } else if (p > 0){
        scalarType sumOfPowers{0};
        for (auto i=0; i < v.size(); ++i){
            sumOfPowers += zlab::pow(std::abs(v[i]), p);
        }
        return zlab::pow(sumOfPowers, 1.0 / p);
    } else {
        throw std::invalid_argument("p must be a positive integer (p > 0) or infinity (std::numeric_limits<double>::infinity()).");
    }
}

template <VectorConcept vectorTypeX, VectorConcept vectorTypeY>
scalarType dot(const vectorTypeX& x, const vectorTypeY& y) {
    assert(x.size() == y.size());
    scalarType result{0};
    for(auto i=0; i < x.size(); i++){
        result += x[i] * y[i];
    }
    return result;
}

template <VectorConcept vectorTypeA, VectorConcept vectorTypeB, VectorConcept vectorTypeC>
void cross(const vectorTypeA& a, const vectorTypeB& b, vectorTypeC& c) {
    assert(a.size() == 3);
    assert(b.size() == 3);
    assert(c.size() == 3);
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

template <typename matrixType>
concept MatrixConcept = requires(const matrixType m, positiveIntegerType i, positiveIntegerType j) {
    m.get_number_of_rows();
    m.get_number_of_columns();
    m(i,j);
};

template <MatrixConcept matrixTypeA, MatrixConcept matrixTypeB, MatrixConcept matrixTypeC>
void gemm(
    const matrixTypeA& A, 
    const matrixTypeB& B, 
    matrixTypeC& C, 
    scalarType a=1,
    scalarType b=1)
{
    assert(C.get_number_of_rows() == A.get_number_of_rows());
    assert(A.get_number_of_columns() == B.get_number_of_rows());
    assert(C.get_number_of_columns() == B.get_number_of_columns());
    for(auto i=0; i<A.get_number_of_rows(); ++i){
        for(auto k=0; k<C.get_number_of_columns(); ++k){
            auto sum = b * C(i, k);
            for(auto j=0; j<B.get_number_of_rows(); ++j){
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
