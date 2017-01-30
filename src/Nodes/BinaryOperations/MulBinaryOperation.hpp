#pragma once
#include "BinaryOperationNode.hpp"
#include "Utils/NotNull.hpp"

template<class Type>
struct MulBinaryOperationNode : BinaryOperationNode<Type>
{
    MulBinaryOperationNode(
            NotNull<ComputationNode<Type>> firstInput,
            NotNull<ComputationNode<Type>> secondInput)
        : m_firstInput(*firstInput)
        , m_secondInput(*secondInput)
    {}

    void forwardPass() override
    {
        m_outputValue = m_firstInput.getOutputValues()[0] * m_secondInput.getOutputValues()[0];
        m_firstError = Type{};
        m_secondError = Type{};
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(m_outputValue);
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        m_firstError += errors[0] * m_secondInput.getOutputValues()[0];
        m_secondError += errors[0] * m_firstInput.getOutputValues()[0];

    }

    void backPropagationPass() override
    {
        m_firstInput.backPropagate(m_firstError);
        m_secondInput.backPropagate(m_secondError);
    }

private:
    ComputationNode<Type>& m_firstInput;
    ComputationNode<Type>& m_secondInput;
    Type m_outputValue;
    Type m_firstError;
    Type m_secondError;
};
