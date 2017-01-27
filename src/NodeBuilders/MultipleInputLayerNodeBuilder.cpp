#include "MultipleInputLayerNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include <algorithm>

MultipleInputLayerNodeBuilder::MultipleInputLayerNodeBuilder(BuilderStorage& builderStorage, std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> factory)
    : m_builderStorage(builderStorage)
    , m_factory(std::move(factory))
{
}

NotNull<MultipleInputNodeBuilder> MultipleInputLayerNodeBuilder::addInput(MultipleInputTag, std::string const& operation)
{
    auto l_builder = m_builderStorage.createMultipleInputNodeBuilder(operation);
    m_inputBuilders.push_back(l_builder);
    m_inputOperationBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<BinaryNodeBuilder> MultipleInputLayerNodeBuilder::addInput(BinaryNodeTag, std::string const& operation)
{
    auto l_builder = m_builderStorage.createBinaryNodeBuilder(operation);
    m_inputBuilders.push_back(l_builder);
    m_inputOperationBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<UnaryNodeBuilder> MultipleInputLayerNodeBuilder::addInput(UnaryNodeTag, std::string const& operation)
{
    auto l_builder = m_builderStorage.createUnaryNodeBuilder(operation);
    m_inputBuilders.push_back(l_builder);
    m_inputOperationBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<VariableNodeBuilder> MultipleInputLayerNodeBuilder::addInput(VariableTag)
{
    auto l_builder = m_builderStorage.createVariableNodeBuilder();
    m_inputBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<ConstNodeBuilder> MultipleInputLayerNodeBuilder::addInput(ConstTag)
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
