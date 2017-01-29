#include "UnaryNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include "BinaryNodeBuilder.hpp"


UnaryNodeBuilder::UnaryNodeBuilder(BuilderStorage& builderStorage, std::unique_ptr<IUnaryOperationNodesFactory<BNN_TYPE>> factory)
    : m_builderStorage(builderStorage)
    , m_factory(std::move(factory))
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

NotNull<BinaryNodeBuilder> UnaryNodeBuilder::setInput(BinaryNodeSpecs specs)
{
    assert(m_inputBuilder == nullptr);
    auto l_builder = m_builderStorage.createBinaryNodeBuilder(std::move(specs.factory));
    m_inputBuilder = l_builder;
    m_operationBuilder = l_builder;
    return l_builder;
}

NotNull<UnaryNodeBuilder> UnaryNodeBuilder::setInput(UnaryNodeSpecs specs)
{
    assert(m_inputBuilder == nullptr);
    auto l_builder = m_builderStorage.createUnaryNodeBuilder(std::move(specs.factory));
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
    return m_factory->create(
                builderToNodeMaps.getComputationNodeFromMaps(m_inputBuilder));
}
