
#pragma once

#include <vector>

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
        
        scalarType& operator()(integerType, integerType);
        const scalarType& operator()(integerType, integerType) const;

        void print() const;
};

} // end namespace zlab
