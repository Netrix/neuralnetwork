#pragma once
#include "Nodes/OperationNode.hpp"
#include "Nodes/VariableNode.hpp"
#include "NotNull.hpp"
#include <memory>
#include <vector>

template<class Type>
struct IPassThroughLayerNodeFactory
{
    virtual std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input) = 0;
};
