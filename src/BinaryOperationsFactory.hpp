#pragma once
#include "NotNull.hpp"
#include "BinaryOperationNode.hpp"
#include "MulBinaryOperation.hpp"
#include "AddBinaryOperation.hpp"

template<class Type>
struct BinaryOperationsFactory
{
    std::unique_ptr<BinaryOperationNode<Type>> create(std::string const& nodeType,
                                                NotNull<ComputationNode<Type>> firstInput,
                                                NotNull<ComputationNode<Type>> secondInput)
    {
        if(nodeType == "mul")
        {
            return std::make_unique<MulBinaryOperationNode<Type>>(firstInput, secondInput);
        }
        else if(nodeType == "add")
        {
            return std::make_unique<AddBinaryOperationNode<Type>>(firstInput, secondInput);
        }
        assert(false);
        return nullptr; // TODO add implementation!!!
    }
};
