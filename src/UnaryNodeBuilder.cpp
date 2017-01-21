#include "UnaryNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include "UnaryOperationsFactory.hpp"
#include "BinaryNodeBuilder.hpp"


UnaryNodeBuilder::UnaryNodeBuilder(BuilderStorage& builderStorage, std::string const& operation)
    : m_builderStorage(builderStorage)
    , m_operation(operation)
{
}

NotNull<BinaryNodeBuilder> UnaryNodeBuilder::setInput(BinaryNodeTag, std::string const& operation)
{
    assert(m_inputBuilder == nullptr);
    auto l_builder = m_builderStorage.createBinaryNodeBuilder(operation);
    m_inputBuilder = l_builder;
    m_operationBuilder = l_builder;
    return l_builder;
}

NotNull<UnaryNodeBuilder> UnaryNodeBuilder::setInput(UnaryNodeTag, std::string const& operation)
{
    assert(m_inputBuilder == nullptr);
    auto l_builder = m_builderStorage.createUnaryNodeBuilder(operation);
    m_inputBuilder = l_builder;
    m_operationBuilder = l_builder;
    return l_builder;
}

NotNull<VariableNodeBuilder> UnaryNodeBuilder::setInput(VariableTag)
{
    assert(m_inputBuilder == nullptr);
    auto l_builder = m_builderStorage.createVariableNodeBuilder();
    m_inputBuilder = l_builder;
    return l_builder;
}

NotNull<ConstNodeBuilder> UnaryNodeBuilder::setInput(ConstTag)
{
    assert(m_inputBuilder == nullptr);
    auto l_builder = m_builderStorage.createConstNodeBuilder();
    m_inputBuilder = l_builder;
    return l_builder;
}

void UnaryNodeBuilder::setInput(NotNull<ConstNodeBuilder> node)
{
    assert(m_inputBuilder == nullptr);
    m_inputBuilder = node;
}

ArrayView<OperationNodeBuilder*> UnaryNodeBuilder::getOperations()
{
    return m_operationBuilder;
}

std::unique_ptr<OperationNode<BNN_TYPE>> UnaryNodeBuilder::build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps)
{
    auto inputNode = getComputationNodeFromMaps(builderToNodeMaps, m_inputBuilder);

    UnaryOperationsFactory<BNN_TYPE> factory;    // TODO Inject it
    return factory.create(m_operation, inputNode);
}

NotNull<ComputationNode<BNN_TYPE>> UnaryNodeBuilder::getComputationNodeFromMaps(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps,
                                                    NotNull<NodeBuilder> nodeBuilder) const
{
    auto constNode = builderToNodeMaps.consts.find(nodeBuilder);
    if(constNode != builderToNodeMaps.consts.end())
    {
        return constNode->second.get();
    }

    auto variableNode = builderToNodeMaps.variables.find(nodeBuilder);
    if(variableNode != builderToNodeMaps.variables.end())
    {
        return variableNode->second.get();
    }

    auto operationNode = builderToNodeMaps.operations.find(nodeBuilder);
    if(operationNode != builderToNodeMaps.operations.end())
    {
        return operationNode->second;
    }

    throw InvalidComputationGraph("Missing input value");
}
