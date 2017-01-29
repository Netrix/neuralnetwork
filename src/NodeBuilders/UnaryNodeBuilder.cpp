#include "UnaryNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include "UnaryOperationsFactory.hpp"
#include "BinaryNodeBuilder.hpp"


UnaryNodeBuilder::UnaryNodeBuilder(BuilderStorage& builderStorage, std::string const& operation)
    : m_builderStorage(builderStorage)
    , m_operation(operation)
{
}

NotNull<MultipleInputNodeBuilder> UnaryNodeBuilder::setInput(MultipleInputNodeSpecs const& specs)
{
    assert(m_inputBuilder == nullptr);
    auto l_builder = m_builderStorage.createMultipleInputNodeBuilder(specs.operation);
    m_inputBuilder = l_builder;
    m_operationBuilder = l_builder;
    return l_builder;
}

NotNull<BinaryNodeBuilder> UnaryNodeBuilder::setInput(BinaryNodeSpecs const& specs)
{
    assert(m_inputBuilder == nullptr);
    auto l_builder = m_builderStorage.createBinaryNodeBuilder(specs.operation);
    m_inputBuilder = l_builder;
    m_operationBuilder = l_builder;
    return l_builder;
}

NotNull<UnaryNodeBuilder> UnaryNodeBuilder::setInput(UnaryNodeSpecs const& specs)
{
    assert(m_inputBuilder == nullptr);
    auto l_builder = m_builderStorage.createUnaryNodeBuilder(specs.operation);
    m_inputBuilder = l_builder;
    m_operationBuilder = l_builder;
    return l_builder;
}

NotNull<VariableNodeBuilder> UnaryNodeBuilder::setInput(VariableNodeSpecs)
{
    assert(m_inputBuilder == nullptr);
    auto l_builder = m_builderStorage.createVariableSingleValueNodeBuilder();
    m_inputBuilder = l_builder;
    return l_builder;
}

NotNull<ConstSingleValueNodeBuilder> UnaryNodeBuilder::setInput(ConstNodeSpecs)
{
    assert(m_inputBuilder == nullptr);
    auto l_builder = m_builderStorage.createConstSingleValueNodeBuilder();
    m_inputBuilder = l_builder;
    return l_builder;
}

void UnaryNodeBuilder::setInput(NotNull<ConstSingleValueNodeBuilder> node)
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
