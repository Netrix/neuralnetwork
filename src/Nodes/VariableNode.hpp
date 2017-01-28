#pragma once
#include <iostream>
#include "ComputationNode.hpp"

template<class Type>
struct VariableNode : ComputationNode<Type> // Single variable node that inherits from VariablesNode
{
    VariableNode(Type & value, Type & delta)
        : m_value(value)
        , m_delta(delta)
    {}

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(m_value);
    }

    std::size_t getNumOutputs() const override
    {
        return 1;
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        m_delta += errors[0];
    }

private:
    Type & m_value;
    Type & m_delta;
};

// TODO this can be common with ConstNode, differ by tag
