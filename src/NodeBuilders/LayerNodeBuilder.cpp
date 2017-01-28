#include "LayerNodeBuilder.hpp"
#include "BuilderStorage.hpp"

LayerNodeBuilder::LayerNodeBuilder(BuilderStorage& builderStorage,
                                   std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> factory)
    : m_builderStorage(builderStorage)
    , m_factory(std::move(factory))
{

}

NotNull<MultipleInputLayerNodeBuilder> LayerNodeBuilder::setInput(MultipleInputLayerNodeTag, std::unique_ptr<IMultipleInputLayerOperationsFactory<BNN_TYPE>> factory)
{
    assert(m_inputBuilder == nullptr);

    auto l_builder = m_builderStorage.createMultipleInputLayerNodeBuilder(std::move(factory));
    m_inputBuilder = l_builder;
    m_inputOperationBuilder = l_builder;
    m_variablesNodeBuilder = allocateVariableNodeBuilder(factory->getNumOutputs());
    return l_builder;
}

NotNull<LayerNodeBuilder> LayerNodeBuilder::setInput(LayerNodeTag, std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> factory)  // TODO replace LayerNodeTag and other tags with SpecsStruct that defines the Input, factory should be taken by name from library
{
    assert(m_inputBuilder == nullptr);

    auto l_builder = m_builderStorage.createLayerNodeBuilder(std::move(factory));
    m_inputBuilder = l_builder;
    m_inputOperationBuilder = l_builder;
    m_variablesNodeBuilder = allocateVariableNodeBuilder(factory->getNumOutputs());
    return l_builder;
}

ArrayView<OperationNodeBuilder*> LayerNodeBuilder::getOperations()
{
    return m_inputOperationBuilder;
}

VariableBufferNodeBuilder* LayerNodeBuilder::allocateVariableNodeBuilder(std::size_t numInputs)
{
    m_builderStorage.createVariableBufferNodeBuilder(m_factory->getNumVariables(numInputs));
}

std::unique_ptr<OperationNode<BNN_TYPE>> LayerNodeBuilder::build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps)
{
    return m_factory->create(builderToNodeMaps.getComputationNodeFromMaps(m_inputBuilder),
                             builderToNodeMaps.getVariableNodeFromMap(m_variablesNodeBuilder));
}
