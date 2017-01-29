#pragma once
#include "LayerNode.hpp"
#include "NotNull.hpp"
#include <algorithm>
#include <cmath>

template<class Type>
struct SigmoidLayerNode : LayerNode<Type>   // add passthrough LayerNode that doesn't need numOutputs because it should get them from parent
{
    SigmoidLayerNode(NotNull<ComputationNode<Type>> inputLayer, Type beta)
        : m_inputLayer(inputLayer)
        , m_beta(beta)
        , m_errors(inputLayer->getNumOutputs())
        , m_outputs(inputLayer->getNumOutputs())
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
            m_errors[i] = (m_beta * m_outputs[i] * ((Type)1.0 - m_outputs[i])) * errors[i];
        }
        m_inputLayer->backPropagate(m_errors);
    }

private:
    Type calculateSigmoid(Type value)
    {
        return 1.0f / (1.0f + exp(m_beta * -value));
    }

private:
    NotNull<ComputationNode<Type>> m_inputLayer;
    Type m_beta = 1.0f;
    std::vector<Type> m_errors;
    std::vector<Type> m_outputs;
};
