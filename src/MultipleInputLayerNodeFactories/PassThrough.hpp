#pragma once

#include "IMultipleInputLayerOperationsFactory.hpp"
#include "Nodes/MultipleInputLayerNodes/PassThroughMultipleInputLayerNode.hpp"

template<class Type>
struct PassThroughMultipleInputLayerNodeFactory : IMultipleInputLayerOperationsFactory<Type>
{
    std::unique_ptr<OperationNode<Type>> create(std::vector<NotNull<ComputationNode<Type>>> const& inputs) override
    {
        return std::make_unique<PassThroughMultipleInputLayerNode<Type>>(inputs);
    }
};
