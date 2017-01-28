#pragma once

#include "ILayerOperationsFactory.hpp"
#include "Nodes/LayerNodes/FullyConnectedLayer.hpp"

template<class Type>
struct FullyConnectedLayerNodeFactory : ILayerOperationsFactory<Type>
{
    FullyConnectedLayerNodeFactory(std::size_t numOutputs)
        : m_numOutputs(numOutputs)
    {}

    std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input,
                                                NotNull<VariableNode<Type>> variables) override
    {
        return std::make_unique<FullyConnectedLayerNode<Type>>(input, variables, m_numOutputs);
    }

    std::size_t getNumOutputs() const override
    {
        return m_numOutputs;
    }

    std::size_t getNumVariables(std::size_t numInputs) const  override
    {
        return m_numOutputs * (numInputs + 1);
    }

private:
    std::size_t m_numOutputs;
};
