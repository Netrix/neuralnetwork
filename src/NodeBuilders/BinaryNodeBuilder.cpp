#include "BinaryNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include "VariableSingleValueNodeBuilder.hpp"

BinaryNodeBuilder::BinaryNodeBuilder(BuilderStorage& builderStorage,
                                     std::unique_ptr<IBinaryOperationNodesFactory<BNN_TYPE>> factory)
    : m_builderStorage(builderStorage)
    , m_factory(std::move(factory))
{
}

NotNull<MultipleInputNodeBuilder> BinaryNodeBuilder::setFirstInput(MultipleInputNodeSpecs specs)
{
    assert(m_inputBuilders[0] == nullptr);
    auto l_builder = m_builderStorage.createMultipleInputNodeBuilder(std::move(specs.factory));
    m_inputBuilders[0] = l_builder;
    m_operationBuilders[0] = l_builder;
    return l_builder;
}

NotNull<MultipleInputNodeBuilder> BinaryNodeBuilder::setSecondInput(MultipleInputNodeSpecs specs)
{
    assert(m_inputBuilders[1] == nullptr);
    auto l_builder = m_builderStorage.createMultipleInputNodeBuilder(std::move(specs.factory));
    m_inputBuilders[1] = l_builder;
    m_operationBuilders[1] = l_builder;
    return l_builder;
}

NotNull<UnaryNodeBuilder> BinaryNodeBuilder::setFirstInput(UnaryNodeSpecs specs)  // change UnarayNodeTag with UnaryNodeSpecs
{
    assert(m_inputBuilders[0] == nullptr);
    auto l_builder = m_builderStorage.createUnaryNodeBuilder(std::move(specs.factory));
    m_inputBuilders[0] = l_builder;
    m_operationBuilders[0] = l_builder;
    return l_builder;
}

NotNull<UnaryNodeBuilder> BinaryNodeBuilder::setSecondInput(UnaryNodeSpecs specs)
{
    assert(m_inputBuilders[1] == nullptr);
    auto l_builder = m_builderStorage.createUnaryNodeBuilder(std::move(specs.factory));
    m_inputBuilders[1] = l_builder;
    m_operationBuilders[1] = l_builder;
    return l_builder;
}

NotNull<BinaryNodeBuilder> BinaryNodeBuilder::setFirstInput(BinaryNodeSpecs specs)
{
    assert(m_inputBuilders[0] == nullptr);
    auto l_builder = m_builderStorage.createBinaryNodeBuilder(std::move(specs.factory));
    m_inputBuilders[0] = l_builder;
    m_operationBuilders[0] = l_builder;
    return l_builder;
}

NotNull<BinaryNodeBuilder> BinaryNodeBuilder::setSecondInput(BinaryNodeSpecs specs)
{
    assert(m_inputBuilders[1] == nullptr);
    auto l_builder = m_builderStorage.createBinaryNodeBuilder(std::move(specs.factory));
    m_inputBuilders[1] = l_builder;
    m_operationBuilders[1] = l_builder;
    return l_builder;
}


NotNull<VariableNodeBuilder> BinaryNodeBuilder::setFirstInput(VariableNodeSpecs)
{
    assert(m_inputBuilders[0] == nullptr);
    auto l_builder = m_builderStorage.createVariableSingleValueNodeBuilder();
    m_inputBuilders[0] = l_builder;
    return l_builder;
}

NotNull<VariableNodeBuilder> BinaryNodeBuilder::setSecondInput(VariableNodeSpecs)
{
    assert(m_inputBuilders[1] == nullptr);
    auto l_builder = m_builderStorage.createVariableSingleValueNodeBuilder();
    m_inputBuilders[1] = l_builder;
    return l_builder;
}


NotNull<ConstSingleValueNodeBuilder> BinaryNodeBuilder::setFirstInput(ConstNodeSpecs)
{
    assert(m_inputBuilders[0] == nullptr);
    auto l_builder = m_builderStorage.createConstSingleValueNodeBuilder();
    m_inputBuilders[0] = l_builder;
    return l_builder;
}

NotNull<ConstSingleValueNodeBuilder> BinaryNodeBuilder::setSecondInput(ConstNodeSpecs)
{
    assert(m_inputBuilders[1] == nullptr);
    auto l_builder = m_builderStorage.createConstSingleValueNodeBuilder();
    m_inputBuilders[1] = l_builder;
    return l_builder;
}

void BinaryNodeBuilder::setFirstInput(NotNull<ConstSingleValueNodeBuilder> node)
{
    m_inputBuilders[0] = node;
}

void BinaryNodeBuilder::setSecondInput(NotNull<ConstSingleValueNodeBuilder> node)
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

    return m_factory->create(firstInputNode, secondInputNode);
}
