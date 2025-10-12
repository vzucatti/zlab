
#pragma once

#include <cmath>

#include "core.hpp"
#include "utilities.hpp"

namespace zlab{

class AbstractRadialBasisFunction{
    protected:
        scalarType radius;
    public:
        AbstractRadialBasisFunction(scalarType radius) : radius(radius) {}
        virtual scalarType evaluate(scalarType r) const = 0;
};

using AbstractRBF = AbstractRadialBasisFunction;

class Bump : public AbstractRBF{
    using Base = AbstractRBF;
    public:
        Bump(scalarType radius) : Base(radius) {}
        scalarType evaluate(scalarType r) const override;
};

}

