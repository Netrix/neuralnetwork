#include "BinaryNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include "BinaryOperationsFactory.hpp"


BinaryNodeBuilder::BinaryNodeBuilder(BuilderStorage& builderStorage, std::string const& operation)
    : m_builderStorage(builderStorage)
    , m_operation(operation)
{
}

NotNull<MultipleInputNodeBuilder> BinaryNodeBuilder::setFirstInput(MultipleInputTag, std::string const& operation)
{
    assert(m_inputBuilders[0] == nullptr);
    auto l_builder = m_builderStorage.createMultipleInputNodeBuilder(operation);
    m_inputBuilders[0] = l_builder;
    m_operationBuilders[0] = l_builder;
    return l_builder;
}

NotNull<MultipleInputNodeBuilder> BinaryNodeBuilder::setSecondInput(MultipleInputTag, std::string const& operation)
{
    assert(m_inputBuilders[1] == nullptr);
    auto l_builder = m_builderStorage.createMultipleInputNodeBuilder(operation);
    m_inputBuilders[1] = l_builder;
    m_operationBuilders[1] = l_builder;
    return l_builder;
}

NotNull<UnaryNodeBuilder> BinaryNodeBuilder::setFirstInput(UnaryNodeTag, std::string const& operation)
{
    assert(m_inputBuilders[0] == nullptr);
    auto l_builder = m_builderStorage.createUnaryNodeBuilder(operation);
    m_inputBuilders[0] = l_builder;
    m_operationBuilders[0] = l_builder;
    return l_builder;
}

NotNull<UnaryNodeBuilder> BinaryNodeBuilder::setSecondInput(UnaryNodeTag, std::string const& operation)
{
    assert(m_inputBuilders[1] == nullptr);
    auto l_builder = m_builderStorage.createUnaryNodeBuilder(operation);
    m_inputBuilders[1] = l_builder;
    m_operationBuilders[1] = l_builder;
    return l_builder;
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
    auto l_builder = m_builderStorage.createVariableSingleValueNodeBuilder();
    m_inputBuilders[0] = l_builder;
    return l_builder;
}

NotNull<VariableNodeBuilder> BinaryNodeBuilder::setSecondInput(VariableTag)
{
    assert(m_inputBuilders[1] == nullptr);
    auto l_builder = m_builderStorage.createVariableSingleValueNodeBuilder();
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

void BinaryNodeBuilder::setFirstInput(NotNull<BinaryNodeBuilder> node)
{
    m_inputBuilders[0] = node;
}

void BinaryNodeBuilder::setSecondInput(NotNull<BinaryNodeBuilder> node)
{
    m_inputBuilders[1] = node;
}

void BinaryNodeBuilder::setFirstInput(NotNull<UnaryNodeBuilder> node)
{
    m_inputBuilders[0] = node;
}

void BinaryNodeBuilder::setSecondInput(NotNull<UnaryNodeBuilder> node)
{
    m_inputBuilders[1] = node;
}

ArrayView<OperationNodeBuilder*> BinaryNodeBuilder::getOperations()
{
    return m_operationBuilders;
}

std::unique_ptr<OperationNode<BNN_TYPE>> BinaryNodeBuilder::build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps)
{
    auto firstInputNode = builderToNodeMaps.getComputationNodeFromMaps(m_inputBuilders[0]);
    auto secondInputNode = builderToNodeMaps.getComputationNodeFromMaps(m_inputBuilders[1]);

    BinaryOperationsFactory<BNN_TYPE> factory;    // TODO Inject it
    return factory.create(m_operation, firstInputNode, secondInputNode);
}
