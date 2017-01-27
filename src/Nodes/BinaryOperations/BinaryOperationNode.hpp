#pragma once
#include "Nodes/OperationNode.hpp"

template<class Type>
struct BinaryOperationNode : OperationNode<Type>
{
    std::size_t getNumOutputs() const override
    {
        return 1;
    }
};
