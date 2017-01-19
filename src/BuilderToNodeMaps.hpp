#pragma once
#include <map>
#include <memory>
#include "ConstNode.hpp"
#include "VariableNode.hpp"
#include "BinaryOperationNode.hpp"

struct ConstNodeBuilder;
struct VariableNodeBuilder;
struct BinaryNodeBuilder;

template<class Type>
using ConstBuilderToNodeMap = std::map<ConstNodeBuilder*, std::unique_ptr<ConstNode<Type>>>;
template<class Type>
using VariableBuilderToNodeMap = std::map<VariableNodeBuilder*, std::unique_ptr<VariableNode<Type>>>;

using OperationBuilderToNodeMap = std::map<BinaryNodeBuilder*, std::unique_ptr<OperationNode>>;

template<class Type>
struct BuilderToNodeMaps
{
    ConstBuilderToNodeMap<Type> consts;
    VariableBuilderToNodeMap<Type> variables;
    OperationBuilderToNodeMap operations;
};
