#pragma once
#include "LayerNode.hpp"
#include "NotNull.hpp"
#include <algorithm>

template<class Type>
struct SigmoidLayerNode : LayerNode<Type>   // add passthrough LayerNode that doesn't need numOutputs because it should get them from parent
{
    SigmoidLayerNode(NotNull<ComputationNode<Type>> inputLayer)
        : m_inputLayer(inputLayer)
        , m_errors(inputLayer.getNumOutputs())
        , m_outputs(inputLayer.getNumOutputs())
    {
    }

    void forwardPass() override
    {
        auto inputs = m_inputLayer->getOutputValues();
        for(auto i = 0u; i < m_outputs.size(); ++i)
        {
            m_outputs[i]  = calculateSigmoid(inputs[i]);
        }
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
            m_errors[i] (m_beta * m_outputs[i] * ((Type)1.0 - m_outputs[i])) * errors[i];
        }
        m_inputLayer->backPropagate(m_errors);
    }

private:
    Type calculateSigmoid(Type value)
    {
        return 1.0f / (1.0f + exp(m_beta * -value));
    }

private:
    Type m_beta = 1.0f; // TODO add as parameter
    NotNull<ComputationNode<Type>> m_inputLayer;
    std::vector<Type> m_errors;
    std::vector<Type> m_outputs;
};
