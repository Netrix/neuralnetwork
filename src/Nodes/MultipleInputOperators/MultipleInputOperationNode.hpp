#pragma once
#include "Nodes/OperationNode.hpp"

template<class Type>
struct MultipleInputOperationNode : OperationNode<Type>
{
    std::size_t getNumOutputs() const override  // TODO create SingleOutputOperationNode
    {
        return 1;
    }
};
