
#include <algorithm>
#include <iostream>
#include <utility>
#include <cassert>
#include <span>

#include "matrix.hpp"

namespace zlab{

ZMatrix::ZMatrix(ZMatrix&& matrix) noexcept : numberOfRows(matrix.numberOfRows), numberOfColumns(matrix.numberOfColumns), data(std::move(matrix.data)) {
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
    if (this == &matrix) return *this;
    assert(matrix.numberOfColumns == numberOfColumns && matrix.numberOfRows == numberOfRows);
    data = matrix.data;
    return *this;
}

ZMatrix& ZMatrix::operator=(ZMatrix&& matrix) noexcept {
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

ZMatrix identity_matrix(integerType numberOfRows){
    assert(numberOfRows > 0);
    auto numberOfColumns = numberOfRows;
    ZMatrix identity_matrix(numberOfRows, numberOfColumns);
    for(auto i=0; i < numberOfRows; ++i){
        identity_matrix(i,i) = 1;
    }
    return identity_matrix;
}

ZVector ZVector::copy() const {
    ZVector clone(size());
    clone.matrix = matrix;
    return clone;
}

ZVector& ZVector::operator=(const std::span<scalarType> view){
    assert(view.size() == size());
    for(auto i=0; i < view.size(); ++i){
        (*this)[i] = view[i];
    }
    return *this;
}

ZVector& ZVector::operator=(const ColumnView& view){
    assert(view.size() == size());
    for(auto i=0; i < view.size(); ++i){
        (*this)[i] = view[i];
    }
    return *this;
}

positiveIntegerType ZMatrix::compute_vector_index(integerType row, integerType column) const {
    assert(row < numberOfRows && column < numberOfColumns);
    return row * numberOfColumns + column;
}

scalarType& ZMatrix::operator()(integerType row, integerType column) {
    return data[compute_vector_index(row,column)];
}

const scalarType& ZMatrix::operator()(integerType row, integerType column) const {
    return data[compute_vector_index(row,column)];
}

std::span<scalarType> ZMatrix::row_view(integerType rowIndex) {
    assert(rowIndex < numberOfRows && rowIndex > -1);
    scalarType* rowStartPointer = data.data() + (rowIndex * numberOfColumns);
    return std::span<scalarType>(rowStartPointer, numberOfColumns);
}

ColumnView ZMatrix::column_view(integerType columnIndex) {
    return ColumnView(*this, columnIndex);
}

ColumnView::ColumnView(
    ZMatrix& matrix,
    integerType columnIndex) : 
    matrix(matrix), 
    columnIndex(columnIndex) {
    assert(columnIndex < matrix.get_number_of_rows() && columnIndex > -1);
}

scalarType& ColumnView::operator[](integerType rowIndex) {
    return matrix(rowIndex, columnIndex); 
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

ZVector::ZVector(integerType size, scalarType fillValue) : matrix(size,1, fillValue) {}

} // end namespace zlab
