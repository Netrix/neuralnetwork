#pragma once

#include "ILayerOperationsFactory.hpp"
#include "Nodes/LayerNodes/FullyConnectedLayer.hpp"

template<class Type>
struct FullyConnectedLayerNodeFactory : ILayerOperationsFactory<Type>
{
    std::unique_ptr<OperationNode<Type>> create(std::vector<NotNull<ComputationNode<Type>>> const& inputs) override
    {
        return std::make_unique<FullyConnectedLayerNode<Type>>(inputs);
    }
};
