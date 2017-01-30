#pragma once
#include "UnaryOperationNode.hpp"
#include "Utils/NotNull.hpp"
#include <algorithm>

template<class Type>
struct PReLUUnaryOperationNode : UnaryOperationNode<Type>
{
    PReLUUnaryOperationNode(
            NotNull<ComputationNode<Type>> input,
            Type parameter = 0.01)
        : m_input(*input)
        , m_parameter(parameter)
    {}

    void forwardPass() override
    {
        auto value = m_input.getOutputValues()[0];
        m_outputValue = std::max(value, value * m_parameter);
        m_error = Type{};
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(m_outputValue);
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        m_error += m_input.getOutputValues()[0] > 0.0 ? errors[0] : m_parameter;
    }

    void backPropagationPass() override
    {
        m_input.backPropagate(m_error);
    }

private:
    ComputationNode<Type>& m_input;
    Type m_parameter;
    Type m_outputValue;
    Type m_error;
};
