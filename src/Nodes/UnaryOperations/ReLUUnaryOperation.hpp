#pragma once
#include "UnaryOperationNode.hpp"
#include "NotNull.hpp"
#include <algorithm>

template<class Type>
struct ReLUUnaryOperationNode : UnaryOperationNode<Type>
{
    ReLUUnaryOperationNode(
            NotNull<ComputationNode<Type>> input)
        : m_input(*input)
    {}

    void forwardPass() override
    {
        m_outputValue = std::max(m_input.getOutputValues()[0], (Type)0);
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(m_outputValue);
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        auto error = m_input.getOutputValues()[0] > 0.0 ? errors[0] : (Type)0.0;
        m_input.backPropagate(error);
    }

private:
    ComputationNode<Type>& m_input;
    Type m_outputValue;
};
