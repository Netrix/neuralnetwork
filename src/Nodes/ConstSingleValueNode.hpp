#pragma once

#include "ConstNode.hpp"

template<class Type>
struct ConstSingleValueNode : ConstNode<Type>
{
    ConstSingleValueNode(Type & value)
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

private:
    Type & m_value;
};
