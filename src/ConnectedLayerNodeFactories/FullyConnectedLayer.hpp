#pragma once

#include "IConnectedLayerNodeFactory.hpp"
#include "Nodes/LayerNodes/FullyConnectedLayer.hpp"

template<class Type>
struct FullyConnectedLayerNodeFactory : IConnectedLayerNodeFactory<Type>
{
    std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input,
                                                NotNull<VariableNode<Type>> variables,
                                                std::size_t numOutputs) override
    {
        return std::make_unique<FullyConnectedLayerNode<Type>>(input, variables, numOutputs);
    }

    std::size_t getNumVariables(std::size_t numInputs, std::size_t numOutputs) const  override
    {
        return numOutputs * (numInputs + 1);
    }
};
