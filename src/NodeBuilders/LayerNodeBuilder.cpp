#include "LayerNodeBuilder.hpp"
#include "BuilderStorage.hpp"

LayerNodeBuilder::LayerNodeBuilder(BuilderStorage& builderStorage,
                                   std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> factory)
    : m_builderStorage(builderStorage)
    , m_factory(std::move(factory))
{

}

NotNull<MultipleInputLayerNodeBuilder> LayerNodeBuilder::setInput(MultipleInputLayerNodeSpecs specs)
{
    assert(m_inputBuilder == nullptr);
    m_variablesNodeBuilder = allocateVariableNodeBuilder(specs.factory->getNumOutputs());

    auto l_builder = m_builderStorage.createMultipleInputLayerNodeBuilder(std::move(specs.factory));
    m_inputBuilder = l_builder;
    m_inputOperationBuilder = l_builder;
    return l_builder;
}

NotNull<LayerNodeBuilder> LayerNodeBuilder::setInput(LayerNodeSpecs specs)  // TODO factory should be taken by name from library
{
    assert(m_inputBuilder == nullptr);
    m_variablesNodeBuilder = allocateVariableNodeBuilder(specs.factory->getNumOutputs());

    auto l_builder = m_builderStorage.createLayerNodeBuilder(std::move(specs.factory));
    m_inputBuilder = l_builder;
    m_inputOperationBuilder = l_builder;
    return l_builder;
}

NotNull<ConstBufferNodeBuilder> LayerNodeBuilder::setInput(ConstBufferNodeSpecs const& specs)
{
    assert(m_inputBuilder == nullptr);
    m_variablesNodeBuilder = allocateVariableNodeBuilder(specs.numConsts);

    auto l_builder = m_builderStorage.createConstBufferNodeBuilder(specs.numConsts);
    m_inputBuilder = l_builder;
    return l_builder;
}

ArrayView<OperationNodeBuilder*> LayerNodeBuilder::getOperations()
{
    return m_inputOperationBuilder;
}

VariableBufferNodeBuilder* LayerNodeBuilder::allocateVariableNodeBuilder(std::size_t numInputs)
{
    return m_builderStorage.createVariableBufferNodeBuilder(m_factory->getNumVariables(numInputs));
}

std::unique_ptr<OperationNode<BNN_TYPE>> LayerNodeBuilder::build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps)
{
    return m_factory->create(builderToNodeMaps.getComputationNodeFromMaps(m_inputBuilder),
                             builderToNodeMaps.getVariableNodeFromMap(m_variablesNodeBuilder));
}
