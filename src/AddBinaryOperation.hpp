#pragma once
#include "BinaryOperationNode.hpp"
#include "NotNull.hpp"

template<class Type>
struct AddBinaryOperationNode : BinaryOperationNode<Type>
{
    AddBinaryOperationNode(
            NotNull<ComputationNode<Type>> firstInput,
            NotNull<ComputationNode<Type>> secondInput)
        : m_firstInput(*firstInput)
        , m_secondInput(*secondInput)
    {}

    void forwardPass() override
    {
        m_outputValue = m_firstInput.getOutputValues()[0] + m_secondInput.getOutputValues()[0];
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(&m_outputValue, 1);
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        m_firstInput.backPropagate(errors[0]);
        m_secondInput.backPropagate(errors[0]);
    }


private:
    ComputationNode<Type>& m_firstInput;
    ComputationNode<Type>& m_secondInput;
    Type m_outputValue;
};
