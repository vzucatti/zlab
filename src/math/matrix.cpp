
#include <algorithm>
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
    ZMatrix clone(numberOfRows, numberOfColumns);
    clone.data = data;
    return clone;
}

ZVector ZVector::copy() const {
    ZVector clone(length());
    clone.matrix = matrix;
    return clone;
}

ZVector& ZVector::operator=(std::span<const scalarType> view){
    assert(view.size() == length());
    for(auto i=0; i < view.size(); ++i){
        (*this)[i] = view[i];
    }
    return *this;
}

ZVector& ZVector::operator=(const ColumnView& view){
    assert(view.size() == length());
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

ColumnView ZMatrix::column_view(integerType columnIndex) const {
    return ColumnView(*this, columnIndex);
}

ColumnView::ColumnView(
    const ZMatrix& matrix,
    integerType columnIndex) : 
    matrix(matrix), 
    columnIndex(columnIndex) {
    assert(columnIndex < matrix.getNumberOfRows() && columnIndex > -1);
}

const scalarType& ColumnView::operator[](integerType rowIndex) const {
    return matrix(rowIndex, columnIndex); 
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

void ZMatrix::fill(scalarType fillValue) {
    std::ranges::fill(data, fillValue);
}

void ZVector::fill(scalarType fillValue) {
    matrix.fill(fillValue);
}

ZVector& ZVector::operator=(const ZVector& v) {
    if (this == &v) return *this;
    matrix = v.matrix;
    return *this;
}

ZVector& ZVector::operator=(ZVector&& v) {
    matrix = std::move(v.matrix);
    return *this;
}

ZVector::ZVector(ZVector&& v) : matrix(std::move(v.matrix)) {}

scalarType ZVector::dot(const ZVector& vector) const {
    assert(vector.length() == length());
    scalarType result{0};
    for(auto i=0; i < vector.length(); i++){
        result += (*this)[i] * vector[i];
    }
    return result;
}

scalarType ZVector::norm(scalarType p) const {
    if (p == std::numeric_limits<scalarType>::infinity()) {
        scalarType max_abs = 0.0;
        for (auto i=0; i < length(); ++i){
            max_abs = std::max(max_abs, std::abs((*this)[i]));
        }
        return max_abs;
    } else if (p > 0){
        scalarType sumOfPowers{0};
        for (auto i=0; i < length(); ++i){
            sumOfPowers += zlab::pow(std::abs((*this)[i]), p);
        }
        return zlab::pow(sumOfPowers, 1.0 / p);
    } else {
        throw std::invalid_argument("p must be a positive integer (p > 0) or infinity (std::numeric_limits<double>::infinity()).");
    }
}

} // end namespace zlab
