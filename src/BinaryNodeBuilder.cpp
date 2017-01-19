#include "BinaryNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include "BinaryOperationsFactory.hpp"


BinaryNodeBuilder::BinaryNodeBuilder(BuilderStorage& builderStorage, std::string const& operation)
    : m_builderStorage(builderStorage)
    , m_operation(operation)
{
}

NotNull<BinaryNodeBuilder> BinaryNodeBuilder::setFirstInput(BinaryNodeTag, std::string const& operation)
{
    assert(m_inputBuilders[0] == nullptr);
    auto l_builder = m_builderStorage.createBinaryNodeBuilder(operation);
    m_inputBuilders[0] = l_builder;
    m_operationBuilders[0] = l_builder;
    return l_builder;
}

NotNull<BinaryNodeBuilder> BinaryNodeBuilder::setSecondInput(BinaryNodeTag, std::string const& operation)
{
    assert(m_inputBuilders[1] == nullptr);
    auto l_builder = m_builderStorage.createBinaryNodeBuilder(operation);
    m_inputBuilders[1] = l_builder;
    m_operationBuilders[1] = l_builder;
    return l_builder;
}


NotNull<VariableNodeBuilder> BinaryNodeBuilder::setFirstInput(VariableTag)
{
    assert(m_inputBuilders[0] == nullptr);
    auto l_builder = m_builderStorage.createVariableNodeBuilder();
    m_inputBuilders[0] = l_builder;
    return l_builder;
}

NotNull<VariableNodeBuilder> BinaryNodeBuilder::setSecondInput(VariableTag)
{
    assert(m_inputBuilders[1] == nullptr);
    auto l_builder = m_builderStorage.createVariableNodeBuilder();
    m_inputBuilders[1] = l_builder;
    return l_builder;
}


NotNull<ConstNodeBuilder> BinaryNodeBuilder::setFirstInput(ConstTag)
{
    assert(m_inputBuilders[0] == nullptr);
    auto l_builder = m_builderStorage.createConstNodeBuilder();
    m_inputBuilders[0] = l_builder;
    return l_builder;
}

NotNull<ConstNodeBuilder> BinaryNodeBuilder::setSecondInput(ConstTag)
{
    assert(m_inputBuilders[1] == nullptr);
    auto l_builder = m_builderStorage.createConstNodeBuilder();
    m_inputBuilders[1] = l_builder;
    return l_builder;
}

void BinaryNodeBuilder::setFirstInput(NotNull<ConstNodeBuilder> node)
{
    m_inputBuilders[0] = node;
}

void BinaryNodeBuilder::setSecondInput(NotNull<ConstNodeBuilder> node)
{
    m_inputBuilders[1] = node;
}

ArrayView<BinaryNodeBuilder*> BinaryNodeBuilder::getOperations()
{
    return m_operationBuilders;
}

std::unique_ptr<BinaryOperationNode> BinaryNodeBuilder::build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps)
{
    auto firstInputNode = getComputationNodeFromMaps(builderToNodeMaps, m_inputBuilders[0]);
    auto secondInputNode = getComputationNodeFromMaps(builderToNodeMaps, m_inputBuilders[1]);

    BinaryOperationsFactory factory;    // TODO Inject it
    return factory.create(m_operation, firstInputNode, secondInputNode);
}

NotNull<ComputationNode> BinaryNodeBuilder::getComputationNodeFromMaps(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps,
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
