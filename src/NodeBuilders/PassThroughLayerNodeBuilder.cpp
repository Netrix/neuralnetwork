#include "PassThroughLayerNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include "ConnectedLayerNodeBuilder.hpp"
#include "ConstBufferNodeBuilder.hpp"
#include "VariableSingleValueNodeBuilder.hpp"
#include "VariableBufferNodeBuilder.hpp"

PassThroughLayerNodeBuilder::PassThroughLayerNodeBuilder(BuilderStorage& builderStorage, PassThroughLayerNodeSpecs specs)
    : m_builderStorage(builderStorage)
    , m_specs(std::move(specs))
{
}

NotNull<MultipleInputLayerNodeBuilder> PassThroughLayerNodeBuilder::setInput(MultipleInputLayerNodeSpecs specs)
{
    assert(m_inputBuilder == nullptr);
    assert(m_specs.numOutputs == specs.numOutputs);
    auto l_builder = m_builderStorage.createMultipleInputLayerNodeBuilder(std::move(specs.factory));
    m_inputBuilder = l_builder;
    m_inputOperationBuilder = l_builder;
    return l_builder;
}

NotNull<ConnectedLayerNodeBuilder> PassThroughLayerNodeBuilder::setInput(ConnectedLayerNodeSpecs specs)
{
    assert(m_inputBuilder == nullptr);
    assert(m_specs.numOutputs == specs.numOutputs);

    auto l_builder = m_builderStorage.createConnectedLayerNodeBuilder(std::move(specs));
    m_inputBuilder = l_builder;
    m_inputOperationBuilder = l_builder;
    return l_builder;
}

NotNull<PassThroughLayerNodeBuilder> PassThroughLayerNodeBuilder::setInput(PassThroughLayerNodeSpecs specs)
{
    assert(m_inputBuilder == nullptr);
    assert(m_specs.numOutputs == specs.numOutputs);

    auto l_builder = m_builderStorage.createPassThroughLayerNodeBuilder(std::move(specs));
    m_inputBuilder = l_builder;
    m_inputOperationBuilder = l_builder;
    return l_builder;
}

NotNull<ConstBufferNodeBuilder> PassThroughLayerNodeBuilder::setInput(ConstBufferNodeSpecs const& specs)
{
    assert(m_inputBuilder == nullptr);
    assert(m_specs.numOutputs == specs.numConsts);

    auto l_builder = m_builderStorage.createConstBufferNodeBuilder(specs.numConsts);
    m_inputBuilder = l_builder;
    return l_builder;
}

ArrayView<OperationNodeBuilder*> PassThroughLayerNodeBuilder::getOperations()
{
    return m_inputOperationBuilder;
}

std::unique_ptr<OperationNode<BNN_TYPE>> PassThroughLayerNodeBuilder::build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps)
{
    return m_specs.factory->create(builderToNodeMaps.getComputationNodeFromMaps(m_inputBuilder));
}
