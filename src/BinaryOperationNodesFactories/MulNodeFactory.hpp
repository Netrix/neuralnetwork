#pragma once
#include "IBinaryOperationNodesFactory.hpp"
#include "Nodes/BinaryOperations/MulBinaryOperation.hpp"

template<class Type>
struct MulNodeFactory : IBinaryOperationNodesFactory<Type>
{
    std::unique_ptr<BinaryOperationNode<Type>> create(NotNull<ComputationNode<Type>> firstInput,
                                                       NotNull<ComputationNode<Type>> secondInput) override
    {
        return std::make_unique<MulBinaryOperationNode<Type>>(firstInput, secondInput);
    }
};
