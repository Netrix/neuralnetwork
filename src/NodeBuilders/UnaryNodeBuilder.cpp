#include "UnaryNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include "UnaryOperationsFactory.hpp"
#include "BinaryNodeBuilder.hpp"


UnaryNodeBuilder::UnaryNodeBuilder(BuilderStorage& builderStorage, std::string const& operation)
    : m_builderStorage(builderStorage)
    , m_operation(operation)
{
}

NotNull<MultipleInputNodeBuilder> UnaryNodeBuilder::setInput(MultipleInputTag, std::string const& operation)
{
    assert(m_inputBuilder == nullptr);
    auto l_builder = m_builderStorage.createMultipleInputNodeBuilder(operation);
    m_inputBuilder = l_builder;
    m_operationBuilder = l_builder;
    return l_builder;
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
    auto inputNode = builderToNodeMaps.getComputationNodeFromMaps(m_inputBuilder);

    UnaryOperationsFactory<BNN_TYPE> factory;    // TODO Inject it
    return factory.create(m_operation, inputNode);
}
