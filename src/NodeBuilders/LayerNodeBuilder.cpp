#include "LayerNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include <algorithm>

LayerNodeBuilder::LayerNodeBuilder(BuilderStorage& builderStorage, std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> factory)
    : m_builderStorage(builderStorage)
    , m_factory(std::move(factory))
{
}

NotNull<MultipleInputNodeBuilder> LayerNodeBuilder::addInput(MultipleInputTag, std::string const& operation)
{

}

NotNull<BinaryNodeBuilder> LayerNodeBuilder::addInput(BinaryNodeTag, std::string const& operation)
{
    auto l_builder = m_builderStorage.createBinaryNodeBuilder(operation);
    m_inputBuilders.push_back(l_builder);
    m_inputOperationBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<UnaryNodeBuilder> LayerNodeBuilder::addInput(UnaryNodeTag, std::string const& operation)
{
    auto l_builder = m_builderStorage.createUnaryNodeBuilder(operation);
    m_inputBuilders.push_back(l_builder);
    m_inputOperationBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<VariableNodeBuilder> LayerNodeBuilder::addInput(VariableTag)
{
    auto l_builder = m_builderStorage.createVariableNodeBuilder();
    m_inputBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<ConstNodeBuilder> LayerNodeBuilder::addInput(ConstTag)
{
    auto l_builder = m_builderStorage.createConstNodeBuilder();
    m_inputBuilders.push_back(l_builder);
    return l_builder;
}

void LayerNodeBuilder::addInput(NotNull<ConstNodeBuilder> node)
{
    m_inputBuilders.push_back(node);
}

ArrayView<OperationNodeBuilder*> LayerNodeBuilder::getOperations()
{
    return m_inputOperationBuilders;
}

std::unique_ptr<OperationNode<BNN_TYPE>> LayerNodeBuilder::build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps)
{
    std::vector<NotNull<ComputationNode<BNN_TYPE>>> l_inputs;
    std::transform(std::begin(m_inputBuilders), std::end(m_inputBuilders), std::back_inserter(l_inputs),
                   [&](auto inputBuilder)
    {
        return builderToNodeMaps.getComputationNodeFromMaps(inputBuilder);
    });
    return m_factory->create(l_inputs);
}
