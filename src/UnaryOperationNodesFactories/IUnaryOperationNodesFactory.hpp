#pragma once
#include "Nodes/UnaryOperations/UnaryOperationNode.hpp"
#include "Utils/NotNull.hpp"
#include <memory>

template<class Type>
struct IUnaryOperationNodesFactory
{
    virtual std::unique_ptr<UnaryOperationNode<Type>> create(NotNull<ComputationNode<Type>> input) = 0;
};
