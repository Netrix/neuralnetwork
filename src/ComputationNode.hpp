#pragma once
#include "ArrayView.hpp"

template<class Type>
struct ComputationNode
{
    virtual ~ComputationNode() = default;

    virtual ArrayView<Type const> getOutputValues() const = 0;
};
