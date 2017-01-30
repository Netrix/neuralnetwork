#pragma once
#include "ArrayView.hpp"
#include "ConstNode.hpp"

template<class Type>
struct ConstBufferNode : ConstNode<Type>
{
    ConstBufferNode(ArrayView<Type> values)
        : m_values(values)
    {
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return m_values;
    }

    std::size_t getNumOutputs() const override
    {
        return m_values.size();
    }

    void backPropagate(ArrayView<Type const>) override
    {
    }

private:
    ArrayView<Type> m_values;
};
