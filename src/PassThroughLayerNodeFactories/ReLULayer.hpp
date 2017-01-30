#pragma once

#include "IPassThroughLayerOperationsFactory.hpp"
#include "Nodes/LayerNodes/ReLULayer.hpp"

template<class Type>
struct ReLULayerNodeFactory : IPassThroughLayerOperationsFactory<Type>
{
    std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input) override
    {
        return std::make_unique<ReLULayerNode<Type>>(input);
    }
};
