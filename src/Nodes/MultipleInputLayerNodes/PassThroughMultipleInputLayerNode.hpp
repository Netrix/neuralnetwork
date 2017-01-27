#pragma once
#include "MultipleInputLayerNode.hpp"
#include "NotNull.hpp"
#include <algorithm>

template<class Type>
struct PassThroughMultipleInputLayerNode : MultipleInputLayerNode<Type>
{
    PassThroughMultipleInputLayerNode(std::vector<NotNull<ComputationNode<Type>>> const& inputs)
        : m_inputs(inputs)
        , m_outputs(inputs.size())
    {}

    void forwardPass() override
    {
        std::transform(std::begin(m_inputs), std::end(m_inputs), std::begin(m_outputs),
                       [](auto const& node)
        {
            return node->getOutputValues()[0];
        });
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return m_outputs;
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        for(std::size_t i = 0; i < errors.size(); ++i)
        {
            m_inputs[i]->backPropagate(errors[i]);
        }
    }

private:
    std::vector<NotNull<ComputationNode<Type>>> m_inputs;
    std::vector<Type> m_outputs;
};
