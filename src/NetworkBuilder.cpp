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
    auto constStorageBuilder = std::make_unique<ConstStorageBuilder<BNN_TYPE>>(m_storage.getNumConsts());
    auto constNodeMap = getConstNodeMap(*constStorageBuilder);

    auto variableStorageBuilder = std::make_unique<VariableStorageBuilder<BNN_TYPE>>(m_storage.getNumVariables());
    auto variableNodeMap = getVariableNodeMap(*variableStorageBuilder);

    auto l_operations = getOperationNodesInTopologicalOrder();
    for(auto operationBuilder : l_operations)
    {
        // 1. Create struct with constNodeMap, variableNodeMap, operationNodeMap
        // 2. Pass struct to operationBuilder
        // 3. Operation builer build should try to find input in any of map and assign it to new node
        // 4. if no builder found then tree is corrupted, should throw an exception
        // 5. if found builder then create operation node, builder should assign input nodes to operation
        // 6. add new operation to vector
//        auto operationNode = operationBuilder->build();
    }

    return nullptr;
}

ConstBuilderToNodeMap<BNN_TYPE> NetworkBuilder::getConstNodeMap(ConstStorageBuilder<BNN_TYPE> & constStorageBuilder) const
{
    std::map<ConstNodeBuilder*, std::unique_ptr<ConstNode<BNN_TYPE>>> constNodeMap;
    for(auto const& builder : m_storage.getConstBuilders())
    {
        constNodeMap.emplace(builder.get(), builder->build(constStorageBuilder));
    }
    return constNodeMap;
}

VariableBuilderToNodeMap<BNN_TYPE> NetworkBuilder::getVariableNodeMap(VariableStorageBuilder<BNN_TYPE> & variableStorageBuilder) const
{
    std::map<VariableNodeBuilder*, std::unique_ptr<VariableNode<BNN_TYPE>>> variableNodeMap;
    for(auto const& builder : m_storage.getVariableBuilders())
    {
        variableNodeMap.emplace(builder.get(), builder->build(variableStorageBuilder));
    }
    return variableNodeMap;
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
