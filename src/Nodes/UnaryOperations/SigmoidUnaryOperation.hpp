#pragma once
#include "UnaryOperationNode.hpp"
#include "Utils/NotNull.hpp"
#include <cmath>

template<class Type>
struct SigmoidUnaryOperationNode : UnaryOperationNode<Type>
{
    SigmoidUnaryOperationNode(
            NotNull<ComputationNode<Type>> input,
            Type beta)
        : m_input(*input)
        , m_beta(beta)
    {}

    void forwardPass() override
    {
        m_outputValue = calculateSigmoid(m_input.getOutputValues()[0]);
        m_error = Type{};
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(m_outputValue);
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        m_error += (m_beta * m_outputValue * ((Type)1.0 - m_outputValue)) * errors[0];
    }

    void backPropagationPass() override
    {
        m_input.backPropagate(m_error);
    }

private:
    Type calculateSigmoid(Type value)
    {
        return 1.0f / (1.0f + exp(m_beta * -value));
    }

private:
    ComputationNode<Type>& m_input;
    Type m_beta;
    Type m_outputValue;
    Type m_error{};
};
