#pragma once

#include "ComputationNode.hpp"

template<class Type>
struct VariableNode : ComputationNode<Type>
{
    VariableNode(Type & value)
        : m_value(value)
    {}

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(&m_value, 1);
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        m_value += errors[0] * m_learningRate;
    }

private:
    Type m_learningRate = 0.01;
    Type & m_value;
};

// TODO this can be common with ConstNode, differ by tag
