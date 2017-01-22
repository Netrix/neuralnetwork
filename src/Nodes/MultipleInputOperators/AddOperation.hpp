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
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(m_outputValue);
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        for(auto node : m_inputs)
        {
            node->backPropagate(errors[0]);
        }
    }

private:
    std::vector<NotNull<ComputationNode<Type>>> m_inputs;
    Type m_outputValue;
};
