#pragma once
#include "Nodes/OperationNode.hpp"

template<class Type>
struct SingleOutputOperationNode : OperationNode<Type>
{
    std::size_t getNumOutputs() const override
    {
        return 1;
    }
};
