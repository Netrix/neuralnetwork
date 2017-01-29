#pragma once
#include <iostream>
#include "ComputationNode.hpp"

template<class Type>
struct VariableNode : ComputationNode<Type> // Single variable node that inherits from VariablesNode
{
};

// TODO this can be common with ConstNode, differ by tag
