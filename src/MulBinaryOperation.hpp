#pragma once
#include "BinaryOperationNode.hpp"
#include "NotNull.hpp"

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
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(m_outputValue);
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        Type firstError = errors[0] * m_secondInput.getOutputValues()[0];
        Type secondError = errors[0] * m_firstInput.getOutputValues()[0];
        m_firstInput.backPropagate(firstError);
        m_secondInput.backPropagate(secondError);
    }

private:
    ComputationNode<Type>& m_firstInput;
    ComputationNode<Type>& m_secondInput;
    Type m_outputValue;
};
