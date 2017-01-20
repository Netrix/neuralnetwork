#pragma once
#include <vector>
#include <memory>

#include "OperationNode.hpp"
#include "ConstNode.hpp"
#include "VariableNode.hpp"
#include "NodeBuilder.hpp" //BNN_TYPE

using OperationNodes = std::vector<std::unique_ptr<OperationNode>>;
using ConstNodes = std::vector<std::unique_ptr<ConstNode<BNN_TYPE>>>;
using VariableNodes = std::vector<std::unique_ptr<VariableNode<BNN_TYPE>>>;

struct BackPropagationNetwork
{
    BackPropagationNetwork(
            OperationNodes && operationNodes,
            ConstNodes && constNodes,
            VariableNodes && variableNodes)
        : m_operationNodes(std::move(operationNodes))
        , m_constNodes(std::move(constNodes))
        , m_variableNodes(std::move(variableNodes))
    {}

private:
    OperationNodes m_operationNodes;
    ConstNodes m_constNodes;
    VariableNodes m_variableNodes;
};
