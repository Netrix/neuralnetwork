#pragma once
#include "Nodes/MultipleInputOperators/MultipleInputOperationNode.hpp"
#include "NotNull.hpp"
#include <memory>

template<class Type>
struct IMultipleInputOperationNodesFactory
{
    virtual std::unique_ptr<MultipleInputOperationNode<Type>> create(std::vector<NotNull<ComputationNode<Type>>> const& inputs) = 0;
};
