#pragma once
#include "UnaryOperationNode.hpp"
#include "NotNull.hpp"
#include <cmath>

template<class Type>
struct SigmoidUnaryOperationNode : UnaryOperationNode<Type>
{
    SigmoidUnaryOperationNode(
            NotNull<ComputationNode<Type>> input)
        : m_input(*input)
    {}

    void forwardPass() override
    {
        m_outputValue = calculateSigmoid(m_input.getOutputValues()[0]);
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(m_outputValue);
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        auto error = (m_beta * m_outputValue * ((Type)1.0 - m_outputValue)) * errors[0];
        m_input.backPropagate(error);
    }

private:
    Type calculateSigmoid(Type value)
    {
        return 1.0f / (1.0f + exp(m_beta * -value));
    }

private:
    Type m_beta = 1.0f; // TODO add as parameter
    ComputationNode<Type>& m_input;
    Type m_outputValue;
};
