#pragma once
#include "LayerNode.hpp"
#include "NotNull.hpp"
#include <algorithm>
#include <cmath>

template<class Type>
struct ReLULayerNode : LayerNode<Type>   // add passthrough LayerNode that doesn't need numOutputs because it should get them from parent
{
    ReLULayerNode(NotNull<ComputationNode<Type>> inputLayer)
        : m_inputLayer(inputLayer)
        , m_errors(inputLayer->getNumOutputs())
        , m_outputs(inputLayer->getNumOutputs())
    {
    }

    void forwardPass() override
    {
        auto inputs = m_inputLayer->getOutputValues();
        for(auto i = 0u; i < m_outputs.size(); ++i)
        {
            m_outputs[i] = std::max(inputs[i], Type{});
        }
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
        for(std::size_t i = 0; i < errors.size(); ++i)
        {
            m_errors[i] += m_inputLayer->getOutputValues()[i] > 0.0 ? errors[i] : Type{};
        }
    }

    void backPropagationPass() override
    {
        m_inputLayer->backPropagate(m_errors);  // TODO this may go to base class because it is the same for every activation
    }

private:
    NotNull<ComputationNode<Type>> m_inputLayer;
    std::vector<Type> m_errors;
    std::vector<Type> m_outputs;
};
