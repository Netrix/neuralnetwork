#pragma once
#include "ArrayView.hpp"

template<class Type>
struct ComputationNode  // TODO change it to BackPropagateComputationNode
{
    virtual ~ComputationNode() = default;

    virtual ArrayView<Type const> getOutputValues() const = 0;

    virtual void backPropagate(ArrayView<Type const> errors) = 0;
};
