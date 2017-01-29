#pragma once
#include "IMultipleInputOperationNodesFactory.hpp"
#include "Nodes/MultipleInputOperators/AddOperation.hpp"

template<class Type>
struct AddNodeFactory : IMultipleInputOperationNodesFactory<Type>
{
    std::unique_ptr<MultipleInputOperationNode<Type>> create(std::vector<NotNull<ComputationNode<Type>>> const& inputs) override
    {
        return std::make_unique<AddOperationNode<Type>>(inputs);
    }
};
