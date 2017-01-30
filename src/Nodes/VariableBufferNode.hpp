#pragma once
#include "ArrayView.hpp"
#include "VariableNode.hpp"

template<class Type>
struct VariableBufferNode : VariableNode<Type>
{
    VariableBufferNode(ArrayView<Type> values, ArrayView<Type> deltas)
        : m_values(values)
        , m_deltas(deltas)
    {
        assert(values.size() == deltas.size());
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return m_values;
    }

    std::size_t getNumOutputs() const override
    {
        return m_values.size();
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        assert(errors.size() == m_deltas.size());
        for(auto i = 0; i < errors.size(); ++i)
        {
            m_deltas[i] += errors[i];   //TODO can make it faster with sse
        }
    }

private:
    ArrayView<Type> m_values;
    ArrayView<Type> m_deltas;
};
