#pragma once
#include "UnaryOperationNode.hpp"
#include "NotNull.hpp"
#include <algorithm>

template<class Type>
struct PReLUUnaryOperationNode : UnaryOperationNode<Type>
{
    PReLUUnaryOperationNode(
            NotNull<ComputationNode<Type>> input)
        : m_input(*input)
    {}

    void forwardPass() override
    {
        auto value = m_input.getOutputValues()[0];
        m_outputValue = std::max(value, value * m_parameter);
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(m_outputValue);
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        auto error = m_input.getOutputValues()[0] > 0.0 ? errors[0] : m_parameter;
        m_input.backPropagate(error);
    }

private:
    Type m_parameter = 0.01;
    ComputationNode<Type>& m_input;
    Type m_outputValue;
};