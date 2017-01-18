#include "NetworkBuilder.hpp"
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
#include <memory>

NotNull<BinaryNodeBuilder> NetworkBuilder::setRootNode(BinaryNode, std::string const& operation)
{
    auto l_builder = m_storage.createBinaryNodeBuilder(operation);
    m_root = l_builder;
    return l_builder;
}

std::unique_ptr<BackPropagationNetwork> NetworkBuilder::buildBackPropagationNetwork() const
{
    auto constStorage = std::make_unique<ConstStorage<BNN_TYPE>>(m_storage.getNumConsts());

//    ConstNode

    auto l_operations = getOperationNodesInTopologicalOrder();
    for(auto operationBuilder : l_operations)
    {
        auto operationNode = operationBuilder->build();
    }

    return nullptr;
}

std::map<ConstNodeBuilder*, ConstNode<BNN_TYPE>> NetworkBuilder::getConstNodeMap(ConstStorage<BNN_TYPE> & constStorage) const
{
    std::map<ConstNodeBuilder*, ConstNode<BNN_TYPE>> constNodeMap;
    for(auto const& builder : m_storage.getConstBuilders())
    {
        constNodeMap.emplace(builder, builder->build(constStorage));
    }
}

std::vector<BinaryNodeBuilder*> NetworkBuilder::getOperationNodesInTopologicalOrder() const
{
    std::set<BinaryNodeBuilder*> uniqueOperations;
    std::vector<BinaryNodeBuilder*> operations;
    std::queue<BinaryNodeBuilder*> queue;
    queue.push(m_root);

    while (!queue.empty())
    {
        auto current = queue.front();
        queue.pop();

        if(uniqueOperations.insert(current).second)
        {
            operations.push_back(current);
            auto operationNodes = current->getOperations();

            for(auto node : operationNodes)
            {
                queue.push(node);
            }
        }
    }

    std::reverse(std::begin(operations), std::end(operations));
    return operations;
}
