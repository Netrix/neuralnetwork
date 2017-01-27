#pragma once

#include "ComputationNode.hpp"

template<class Type>
struct ConstNode : ComputationNode<Type>
{
    ConstNode(Type & value)
        : m_value(value)
    {}

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(&m_value, 1);
    }

    std::size_t getNumOutputs() const override
    {
        return 1;
    }

    void backPropagate(ArrayView<Type const>) override
    {
    }

private:
    Type & m_value;
};
