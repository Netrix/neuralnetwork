#pragma once

#include "PassThroughLayerNodeFactories/IPassThroughLayerNodeFactory.hpp"
#include "Nodes/LayerNodes/ReLULayer.hpp"

template<class Type>
struct ReLULayerNodeFactory : IPassThroughLayerNodeFactory<Type>
{
    std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input) override
    {
        return std::make_unique<ReLULayerNode<Type>>(input);
    }
};
