#pragma once

#include "ComputationNode.hpp"

template<class Type>
struct VariableNode : ComputationNode<Type>
{
    VariableNode(Type & value)
        : m_value(value)
    {}

    ArrayView<Type const> getOutputValues() const
    {
        return ArrayView<Type const>(&m_value, 1);
    }

private:
    Type & m_value;
};

// TODO this can be common with ConstNode, differ by tag
