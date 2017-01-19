#include "NetworkBuilder.hpp"
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
#include <memory>

NotNull<BinaryNodeBuilder> NetworkBuilder::setRootNode(BinaryNodeTag, std::string const& operation)
{
    auto l_builder = m_storage.createBinaryNodeBuilder(operation);
    m_root = l_builder;
    return l_builder;
}

std::unique_ptr<BackPropagationNetwork> NetworkBuilder::buildBackPropagationNetwork() const
{
    auto constStorageBuilder = std::make_unique<ConstStorageBuilder<BNN_TYPE>>(m_storage.getNumConsts());
    auto variableStorageBuilder = std::make_unique<VariableStorageBuilder<BNN_TYPE>>(m_storage.getNumVariables());

    BuilderToNodeMaps<BNN_TYPE> builderToNodeMaps = {
        getConstNodeMap(*constStorageBuilder),
        getVariableNodeMap(*variableStorageBuilder),
    };

    auto l_operations = getOperationNodesInTopologicalOrder();
    std::vector<std::unique_ptr<OperationNode>> operationNodes;
    operationNodes.reserve(l_operations.size());
    for(auto operationBuilder : l_operations)
    {
        auto operation = operationBuilder->build(builderToNodeMaps);
        builderToNodeMaps.operations.emplace(operationBuilder, operation.get());
        operationNodes.push_back(std::move(operation));
        // DONE: 1. Create struct with constNodeMap, variableNodeMap, operationNodeMap
        // DONE: 2. Pass struct to operationBuilder
        // DONE: 3. Operation builer build should try to find input in any of map and assign it to new node
        // DONE: 4. if no builder found then tree is corrupted, should throw an exception
        // 5. if found builder then create operation node, builder should assign input nodes to operation
        // 6. add new operation to vector
    }

    return nullptr;
}

ConstBuilderToNodeMap<BNN_TYPE> NetworkBuilder::getConstNodeMap(ConstStorageBuilder<BNN_TYPE> & constStorageBuilder) const
{
    std::map<NodeBuilder*, std::unique_ptr<ConstNode<BNN_TYPE>>> constNodeMap;
    for(auto const& builder : m_storage.getConstBuilders())
    {
        constNodeMap.emplace(builder.get(), builder->build(constStorageBuilder));
    }
    return constNodeMap;
}

VariableBuilderToNodeMap<BNN_TYPE> NetworkBuilder::getVariableNodeMap(VariableStorageBuilder<BNN_TYPE> & variableStorageBuilder) const
{
    std::map<NodeBuilder*, std::unique_ptr<VariableNode<BNN_TYPE>>> variableNodeMap;
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
