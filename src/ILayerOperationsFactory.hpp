#pragma once
#include "Nodes/OperationNode.hpp"
#include "NotNull.hpp"
#include <memory>
#include <vector>

template<class Type>
struct ILayerOperationsFactory
{
    virtual std::unique_ptr<OperationNode<Type>> create(std::vector<NotNull<ComputationNode<Type>>> const& inputs) = 0;
};
