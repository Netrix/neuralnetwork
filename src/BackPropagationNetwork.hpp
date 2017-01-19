#pragma once
#include <vector>

struct OperationNode;

struct BackPropagationNetwork
{
private:
    std::vector<OperationNode*> m_nodes;
};
