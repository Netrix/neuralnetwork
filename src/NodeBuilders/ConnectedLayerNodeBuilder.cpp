#include "ConnectedLayerNodeBuilder.hpp"
#include "BuilderStorage.hpp"

ConnectedLayerNodeBuilder::ConnectedLayerNodeBuilder(BuilderStorage& builderStorage, ConnectedLayerNodeSpecs specs)
    : m_builderStorage(builderStorage)
    , m_specs(std::move(specs))
{
}

NotNull<MultipleInputLayerNodeBuilder> ConnectedLayerNodeBuilder::setInput(MultipleInputLayerNodeSpecs specs)
{
    assert(m_inputBuilder == nullptr);
    m_variablesNodeBuilder = allocateVariableNodeBuilder(specs.numOutputs, m_specs.numOutputs);

    auto l_builder = m_builderStorage.createMultipleInputLayerNodeBuilder(std::move(specs.factory));
    m_inputBuilder = l_builder;
    m_inputOperationBuilder = l_builder;
    return l_builder;
}

NotNull<ConnectedLayerNodeBuilder> ConnectedLayerNodeBuilder::setInput(ConnectedLayerNodeSpecs specs)
{
    assert(m_inputBuilder == nullptr);
    m_variablesNodeBuilder = allocateVariableNodeBuilder(specs.numOutputs, m_specs.numOutputs);

    auto l_builder = m_builderStorage.createConnectedLayerNodeBuilder(std::move(specs));
    m_inputBuilder = l_builder;
    m_inputOperationBuilder = l_builder;
    return l_builder;
}

NotNull<PassThroughLayerNodeBuilder> ConnectedLayerNodeBuilder::setInput(PassThroughLayerNodeSpecs specs)
{
    assert(m_inputBuilder == nullptr);
    m_variablesNodeBuilder = allocateVariableNodeBuilder(specs.numOutputs, m_specs.numOutputs);

    auto l_builder = m_builderStorage.createPassThroughLayerNodeBuilder(std::move(specs));
    m_inputBuilder = l_builder;
    m_inputOperationBuilder = l_builder;
    return l_builder;
}

NotNull<ConstBufferNodeBuilder> ConnectedLayerNodeBuilder::setInput(ConstBufferNodeSpecs const& specs)
{
    assert(m_inputBuilder == nullptr);
    m_variablesNodeBuilder = allocateVariableNodeBuilder(specs.numConsts, m_specs.numOutputs);

    auto l_builder = m_builderStorage.createConstBufferNodeBuilder(specs.numConsts);
    m_inputBuilder = l_builder;
    return l_builder;
}

ArrayView<OperationNodeBuilder*> ConnectedLayerNodeBuilder::getOperations()
{
    return m_inputOperationBuilder;
}

VariableBufferNodeBuilder* ConnectedLayerNodeBuilder::allocateVariableNodeBuilder(std::size_t numInputs, std::size_t numOutputs)
{
    return m_builderStorage.createVariableBufferNodeBuilder(m_specs.factory->getNumVariables(numInputs, numOutputs));
}

std::unique_ptr<OperationNode<BNN_TYPE>> ConnectedLayerNodeBuilder::build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps)
{
    return m_specs.factory->create(builderToNodeMaps.getComputationNodeFromMaps(m_inputBuilder),
                                   builderToNodeMaps.getVariableNodeFromMap(m_variablesNodeBuilder),
                                   m_specs.numOutputs);
}
