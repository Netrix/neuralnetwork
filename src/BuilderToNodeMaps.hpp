#pragma once
#include <map>
#include <memory>
#include "Nodes/ConstNode.hpp"
#include "Nodes/VariableNode.hpp"
#include "Nodes/OperationNode.hpp"
#include "Utils/NotNull.hpp"

struct NodeBuilder;

template<class Type>
using ConstBuilderToNodeMap = std::map<NodeBuilder*, std::unique_ptr<ConstNode<Type>>>;
template<class Type>
using VariableBuilderToNodeMap = std::map<NodeBuilder*, std::unique_ptr<VariableNode<Type>>>;
template<class Type>
using OperationBuilderToNodeMap = std::map<NodeBuilder*, NotNull<OperationNode<Type>>>;

struct InvalidComputationGraph : std::runtime_error
{
    InvalidComputationGraph(std::string const& msg)
        : runtime_error(msg)
    {}
};

template<class Type>
struct BuilderToNodeMaps
{
    ConstBuilderToNodeMap<Type> consts;
    VariableBuilderToNodeMap<Type> variables;
    OperationBuilderToNodeMap<Type> operations;

    NotNull<VariableNode<Type>> getVariableNodeFromMap(NotNull<NodeBuilder> nodeBuilder) const
    {
        auto variableNode = variables.find(nodeBuilder);
        if(variableNode != variables.end())
        {
            return variableNode->second.get();
        }

        assert(false);
        throw InvalidComputationGraph("Missing variable node");
    }

    NotNull<ComputationNode<Type>> getComputationNodeFromMaps(NotNull<NodeBuilder> nodeBuilder) const
    {
        auto constNode = consts.find(nodeBuilder);
        if(constNode != consts.end())
        {
            return constNode->second.get();
        }

        auto variableNode = variables.find(nodeBuilder);
        if(variableNode != variables.end())
        {
            return variableNode->second.get();
        }

        auto operationNode = operations.find(nodeBuilder);
        if(operationNode != operations.end())
        {
            return operationNode->second;
        }

        throw InvalidComputationGraph("Missing input value");
    }
};
