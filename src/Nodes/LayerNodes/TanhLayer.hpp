#pragma once
#include "LayerNode.hpp"
#include "NotNull.hpp"
#include <algorithm>
#include <cmath>

template<class Type>
struct TanhLayerNode : LayerNode<Type>
{
    TanhLayerNode(NotNull<ComputationNode<Type>> inputLayer, std::size_t beta)
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
            m_outputs[i] = calculateTanh(inputs[i]);
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
            m_errors[i] += ((Type)1.0 - m_outputs[i] * m_outputs[i]) * errors[i];
        }
    }

    void backPropagationPass() override
    {
        m_inputLayer->backPropagate(m_errors);
    }

private:
    Type calculateTanh(Type value)
    {
        auto expResult = exp(m_beta * -value);
        return (1.0f - expResult) / (1.0f + expResult);
    }


private:
    NotNull<ComputationNode<Type>> m_inputLayer;
    Type m_beta = 1.0f;
    std::vector<Type> m_errors;
    std::vector<Type> m_outputs;
};
