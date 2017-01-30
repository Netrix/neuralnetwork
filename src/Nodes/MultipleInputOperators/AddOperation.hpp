#pragma once
#include "MultipleInputOperationNode.hpp"
#include "NotNull.hpp"
#include <numeric>

template<class Type>
struct AddOperationNode : MultipleInputOperationNode<Type>
{
    AddOperationNode(std::vector<NotNull<ComputationNode<Type>>> const& inputs)
        : m_inputs(inputs)
    {}

    void forwardPass() override
    {
        m_outputValue = std::accumulate(std::begin(m_inputs), std::end(m_inputs), Type{}, [](auto sum, auto node)
        {
            return sum + node->getOutputValues()[0];
        });
        m_error = Type{};
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(m_outputValue);
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        m_error += errors[0];
    }
    void backPropagationPass() override
    {
        for(auto node : m_inputs)
        {
            node->backPropagate(m_error);
        }
    }

private:
    std::vector<NotNull<ComputationNode<Type>>> m_inputs;
    Type m_outputValue;
    Type m_error;
};
