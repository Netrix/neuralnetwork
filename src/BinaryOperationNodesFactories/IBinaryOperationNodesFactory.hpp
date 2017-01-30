#pragma once
#include "Nodes/BinaryOperations/BinaryOperationNode.hpp"
#include "Utils/NotNull.hpp"
#include <memory>

template<class Type>
struct IBinaryOperationNodesFactory
{
    virtual std::unique_ptr<BinaryOperationNode<Type>> create(NotNull<ComputationNode<Type>> firstInput,
                                                              NotNull<ComputationNode<Type>> secondInput) = 0;
};
