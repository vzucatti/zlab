
#include <iostream>
#include <utility>
#include <limits>
#include <cassert>
#include <span>

#include "utilities.hpp"
#include "matrix.hpp"

namespace zlab{

ZMatrix::ZMatrix(ZMatrix&& matrix) : numberOfRows(matrix.numberOfRows), numberOfColumns(matrix.numberOfColumns), data(std::move(matrix.data)) {
    matrix.numberOfRows = 0;
    matrix.numberOfColumns = 0;
}

ZMatrix::ZMatrix(
    integerType numberOfRows, 
    integerType numberOfColumns,
    scalarType fillValue) : 
    numberOfRows(numberOfRows), 
    numberOfColumns(numberOfColumns),
    data(numberOfRows * numberOfColumns, fillValue) {
    assert(numberOfRows > 0 && numberOfColumns > 0);
}

ZMatrix& ZMatrix::operator=(const ZMatrix& matrix){
    assert(matrix.numberOfColumns == numberOfColumns && matrix.numberOfRows == numberOfRows);
    data = matrix.data;
    return *this;
}

ZMatrix& ZMatrix::operator=(ZMatrix&& matrix){
    assert(matrix.numberOfColumns == numberOfColumns && matrix.numberOfRows == numberOfRows);
    data = std::move(matrix.data);
    matrix.numberOfRows = 0;
    matrix.numberOfColumns = 0;
    return *this;
}

ZMatrix ZMatrix::copy() const {
    ZMatrix clone(this->numberOfRows, this->numberOfColumns);
    clone.data = this->data;
    return clone;
}

ZVector ZVector::copy() const {
    ZVector clone(this->numberOfRows);
    clone.data = this->data;
    return clone;
}

ZVector& ZVector::operator=(std::span<const scalarType> view){
    assert(view.size() == (*this).length());
    for(auto i=0; i < view.size(); ++i){
        (*this)[i] = view[i];
    }
    return *this;
}

positiveIntegerType ZMatrix::computeVectorIndex(integerType row, integerType column) const {
    assert(row < numberOfRows && column < numberOfColumns);
    return row * numberOfColumns + column;
}

scalarType& ZMatrix::operator()(integerType row, integerType column) {
    return data[computeVectorIndex(row,column)];
}

const scalarType& ZMatrix::operator()(integerType row, integerType column) const {
    return data[computeVectorIndex(row,column)];
}

std::span<const scalarType> ZMatrix::row_view(integerType rowIndex) const{
    assert(rowIndex < numberOfRows && rowIndex > -1);
    const scalarType* rowStartPointer = data.data() + (rowIndex * numberOfColumns);
    return std::span<const scalarType>(rowStartPointer, numberOfColumns);
}

positiveIntegerType ZMatrix::get_number_of_elements() const{
    return numberOfRows*numberOfColumns;
}

void ZMatrix::print() const {
    using int_ = positiveIntegerType;
    for(int_ row=0; row < numberOfRows; row++){
        for(int_ column=0; column < numberOfColumns; column++){
            std::cout << (*this)(row,column);
            std::cout << (column < numberOfColumns - 1 ? " " : "\n");
        }
    }
}

scalarType ZVector::dot(const ZVector& vector) const {
    assert(vector.length() == (*this).length());
    scalarType result{0};
    for(auto i=0; i < vector.length(); i++){
        result += (*this)[i] * vector[i];
    }
    return result;
}

scalarType ZVector::norm(scalarType p) const {
    if (p == std::numeric_limits<scalarType>::infinity()) {
        scalarType max_abs = 0.0;
        for (const auto& val : data) {
            max_abs = std::max(max_abs, std::abs(val));
        }
        return max_abs;
    } else if (p > 0){
        scalarType sumOfPowers{0};
        for (const auto& val : data){
            sumOfPowers += zlab::pow(std::abs(val), p);
        }
        return zlab::pow(sumOfPowers, 1.0 / p);
    } else {
        throw std::invalid_argument("p must be a positive integer (p > 0) or infinity (std::numeric_limits<double>::infinity()).");
    }
}

void axpy(scalarType a, scalarType x, scalarType& y){
    y += a*x;
}

} // end namespace zlab
