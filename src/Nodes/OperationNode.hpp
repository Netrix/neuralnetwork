#pragma once
#include "ComputationNode.hpp"

template<class Type>
struct OperationNode : ComputationNode<Type>
{
    virtual void forwardPass() = 0;
};
