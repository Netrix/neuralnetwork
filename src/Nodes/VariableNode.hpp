#pragma once
#include "ComputationNode.hpp"

template<class Type>
struct VariableNode : ComputationNode<Type>
{
};

// TODO this can be common with ConstNode, differ by tag
