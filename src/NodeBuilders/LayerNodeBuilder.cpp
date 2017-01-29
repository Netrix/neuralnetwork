#include "LayerNodeBuilder.hpp"
#include "BuilderStorage.hpp"

LayerNodeBuilder::LayerNodeBuilder(BuilderStorage& builderStorage, LayerNodeSpecs specs)
    : m_builderStorage(builderStorage)
    , m_specs(std::move(specs))
{
}

NotNull<MultipleInputLayerNodeBuilder> LayerNodeBuilder::setInput(MultipleInputLayerNodeSpecs specs)
{
    assert(m_inputBuilder == nullptr);
    m_variablesNodeBuilder = allocateVariableNodeBuilder(specs.numOutputs, m_specs.numOutputs);

    auto l_builder = m_builderStorage.createMultipleInputLayerNodeBuilder(std::move(specs.factory));
    m_inputBuilder = l_builder;
    m_inputOperationBuilder = l_builder;
    return l_builder;
}

NotNull<LayerNodeBuilder> LayerNodeBuilder::setInput(LayerNodeSpecs specs)  // TODO factory should be taken by name from library
{
    assert(m_inputBuilder == nullptr);
    m_variablesNodeBuilder = allocateVariableNodeBuilder(specs.numOutputs, m_specs.numOutputs);

    auto l_builder = m_builderStorage.createLayerNodeBuilder(std::move(specs));
    m_inputBuilder = l_builder;
    m_inputOperationBuilder = l_builder;
    return l_builder;
}

NotNull<ConstBufferNodeBuilder> LayerNodeBuilder::setInput(ConstBufferNodeSpecs const& specs)
{
    assert(m_inputBuilder == nullptr);
    m_variablesNodeBuilder = allocateVariableNodeBuilder(specs.numConsts, m_specs.numOutputs);

    auto l_builder = m_builderStorage.createConstBufferNodeBuilder(specs.numConsts);
    m_inputBuilder = l_builder;
    return l_builder;
}

ArrayView<OperationNodeBuilder*> LayerNodeBuilder::getOperations()
{
    return m_inputOperationBuilder;
}

VariableBufferNodeBuilder* LayerNodeBuilder::allocateVariableNodeBuilder(std::size_t numInputs, std::size_t numOutputs)
{
    return m_builderStorage.createVariableBufferNodeBuilder(m_specs.factory->getNumVariables(numInputs, numOutputs));
}

std::unique_ptr<OperationNode<BNN_TYPE>> LayerNodeBuilder::build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps)
{
    return m_specs.factory->create(builderToNodeMaps.getComputationNodeFromMaps(m_inputBuilder),
                             builderToNodeMaps.getVariableNodeFromMap(m_variablesNodeBuilder),
                             m_specs.numOutputs);
}
