
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

class WendlandC0 : public AbstractRBF{
    using Base = AbstractRBF;
    public:
        WendlandC0(scalarType radius) : Base(radius) {}
        scalarType evaluate(scalarType r) const override;
};

class WendlandC2 : public AbstractRBF{
    using Base = AbstractRBF;
    public:
        WendlandC2(scalarType radius) : Base(radius) {}
        scalarType evaluate(scalarType r) const override;
};

}

