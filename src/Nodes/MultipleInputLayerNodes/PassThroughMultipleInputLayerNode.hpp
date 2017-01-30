#pragma once
#include "MultipleInputLayerNode.hpp"
#include "Utils/NotNull.hpp"
#include <algorithm>

template<class Type>
struct PassThroughMultipleInputLayerNode : MultipleInputLayerNode<Type>
{
    PassThroughMultipleInputLayerNode(std::vector<NotNull<ComputationNode<Type>>> const& inputs)
        : m_inputs(inputs)
        , m_outputs(inputs.size())
        , m_errors(inputs.size())
    {}

    void forwardPass() override
    {
        std::transform(std::begin(m_inputs), std::end(m_inputs), std::begin(m_outputs),
                       [](auto const& node)
        {
            return node->getOutputValues()[0];
        });
        std::fill(std::begin(m_errors), std::end(m_errors), Type{});
    }

    std::size_t getNumOutputs() const override
    {
        return m_outputs.size();
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return m_outputs;
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        for(std::size_t i = 0; i < m_errors.size(); ++i)
        {
            m_errors[i] += errors[i];
        }
    }

    void backPropagationPass() override
    {
        for(std::size_t i = 0; i < m_errors.size(); ++i)
        {
            m_inputs[i]->backPropagate(m_errors[i]);
        }
    }

private:
    std::vector<NotNull<ComputationNode<Type>>> m_inputs;
    std::vector<Type> m_outputs;
    std::vector<Type> m_errors;
};
