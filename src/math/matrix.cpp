
#include <iostream>
#include <utility>
#include <cassert>

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
    return std::move(clone);
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

void axpy(scalarType a, scalarType x, scalarType& y){
    y += a*x;
}

} // end namespace zlab
