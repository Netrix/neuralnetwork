#pragma once
#include <map>
#include <memory>
#include "ConstNode.hpp"
#include "VariableNode.hpp"
#include "BinaryOperationNode.hpp"
#include "NotNull.hpp"

struct NodeBuilder;

template<class Type>
using ConstBuilderToNodeMap = std::map<NodeBuilder*, std::unique_ptr<ConstNode<Type>>>;
template<class Type>
using VariableBuilderToNodeMap = std::map<NodeBuilder*, std::unique_ptr<VariableNode<Type>>>;
template<class Type>
using OperationBuilderToNodeMap = std::map<NodeBuilder*, NotNull<OperationNode<Type>>>;

template<class Type>
struct BuilderToNodeMaps
{
    ConstBuilderToNodeMap<Type> consts;
    VariableBuilderToNodeMap<Type> variables;
    OperationBuilderToNodeMap<Type> operations;
};
