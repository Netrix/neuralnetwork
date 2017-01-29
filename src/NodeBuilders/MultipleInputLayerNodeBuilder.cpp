#include "MultipleInputLayerNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include <algorithm>

MultipleInputLayerNodeBuilder::MultipleInputLayerNodeBuilder(BuilderStorage& builderStorage, std::unique_ptr<IMultipleInputLayerOperationsFactory<BNN_TYPE>> factory)
    : m_builderStorage(builderStorage)
    , m_factory(std::move(factory))
{
}

NotNull<MultipleInputNodeBuilder> MultipleInputLayerNodeBuilder::addInput(MultipleInputNodeSpecs const& specs)
{
    auto l_builder = m_builderStorage.createMultipleInputNodeBuilder(specs.operation);
    m_inputBuilders.push_back(l_builder);
    m_inputOperationBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<BinaryNodeBuilder> MultipleInputLayerNodeBuilder::addInput(BinaryNodeSpecs const& specs)
{
    auto l_builder = m_builderStorage.createBinaryNodeBuilder(specs.operation);
    m_inputBuilders.push_back(l_builder);
    m_inputOperationBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<UnaryNodeBuilder> MultipleInputLayerNodeBuilder::addInput(UnaryNodeSpecs const& specs)
{
    auto l_builder = m_builderStorage.createUnaryNodeBuilder(specs.operation);
    m_inputBuilders.push_back(l_builder);
    m_inputOperationBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<VariableNodeBuilder> MultipleInputLayerNodeBuilder::addInput(VariableNodeSpecs)
{
    auto l_builder = m_builderStorage.createVariableSingleValueNodeBuilder();
    m_inputBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<ConstNodeBuilder> MultipleInputLayerNodeBuilder::addInput(ConstNodeSpecs)
{
    auto l_builder = m_builderStorage.createConstNodeBuilder();
    m_inputBuilders.push_back(l_builder);
    return l_builder;
}

void MultipleInputLayerNodeBuilder::addInput(NotNull<ConstNodeBuilder> node)
{
    m_inputBuilders.push_back(node);
}

ArrayView<OperationNodeBuilder*> MultipleInputLayerNodeBuilder::getOperations()
{
    return m_inputOperationBuilders;
}

std::unique_ptr<OperationNode<BNN_TYPE>> MultipleInputLayerNodeBuilder::build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps)
{
    std::vector<NotNull<ComputationNode<BNN_TYPE>>> l_inputs;
    std::transform(std::begin(m_inputBuilders), std::end(m_inputBuilders), std::back_inserter(l_inputs),
                   [&](auto inputBuilder)
    {
        return builderToNodeMaps.getComputationNodeFromMaps(inputBuilder);
    });
    return m_factory->create(l_inputs);
}
