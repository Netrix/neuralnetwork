#include "MultipleInputNodeBuilder.hpp"
#include "Nodes/MultipleInputOperators/MultipleInputOperationNode.hpp"
#include "BuilderStorage.hpp"
#include "MultipleInputOperationsFactory.hpp"
#include <algorithm>

MultipleInputNodeBuilder::MultipleInputNodeBuilder(BuilderStorage& builderStorage, std::string const& operation)
    : m_builderStorage(builderStorage)
    , m_operation(operation)
{
}

NotNull<UnaryNodeBuilder> MultipleInputNodeBuilder::addInput(UnaryNodeTag, std::string const& operation)
{
    auto l_builder = m_builderStorage.createUnaryNodeBuilder(operation);
    m_inputBuilders.push_back(l_builder);
    m_operationBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<BinaryNodeBuilder> MultipleInputNodeBuilder::addInput(BinaryNodeTag, std::string const& operation)
{
    auto l_builder = m_builderStorage.createBinaryNodeBuilder(operation);
    m_inputBuilders.push_back(l_builder);
    m_operationBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<VariableNodeBuilder> MultipleInputNodeBuilder::addInput(VariableTag)
{
    auto l_builder = m_builderStorage.createVariableNodeBuilder();
    m_inputBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<ConstNodeBuilder> MultipleInputNodeBuilder::addInput(ConstTag)
{
    auto l_builder = m_builderStorage.createConstNodeBuilder();
    m_inputBuilders.push_back(l_builder);
    return l_builder;
}

void MultipleInputNodeBuilder::addInput(NotNull<ConstNodeBuilder> node)
{
    m_inputBuilders.push_back(node);
}

ArrayView<OperationNodeBuilder*> MultipleInputNodeBuilder::getOperations()
{
    return m_operationBuilders;
}

std::unique_ptr<OperationNode<BNN_TYPE>> MultipleInputNodeBuilder::build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps)
{
    std::vector<NotNull<ComputationNode<BNN_TYPE>>> l_inputs;
    std::transform(std::begin(m_inputBuilders), std::end(m_inputBuilders), std::back_inserter(l_inputs),
                   [&](auto inputBuilder)
    {
        return builderToNodeMaps.getComputationNodeFromMaps(inputBuilder);
    });

    MultipleInputOperationsFactory<BNN_TYPE> factory;    // TODO Inject it
    return factory.create(m_operation, l_inputs);
}


