#pragma once

#include "ILayerOperationsFactory.hpp"
#include "Nodes/MultipleInputLayerNodes/PassThroughMultipleInputLayerNode.hpp"

template<class Type>
struct PassThroughMultipleInputLayerNodeFactory : ILayerOperationsFactory<Type>
{
    std::unique_ptr<OperationNode<Type>> create(std::vector<NotNull<ComputationNode<Type>>> const& inputs) override
    {
        return std::make_unique<PassThroughMultipleInputLayerNode<Type>>(inputs);
    }
};
