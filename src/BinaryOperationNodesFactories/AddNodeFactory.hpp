#pragma once
#include "IBinaryOperationNodesFactory.hpp"
#include "Nodes/BinaryOperations/AddBinaryOperation.hpp"

template<class Type>
struct AddNodeFactory : IBinaryOperationNodesFactory<Type>
{
    std::unique_ptr<BinaryOperationNode<Type>> create(NotNull<ComputationNode<Type>> firstInput,
                                                       NotNull<ComputationNode<Type>> secondInput) override
    {
        return std::make_unique<AddBinaryOperationNode<Type>>(firstInput, secondInput);
    }
};
