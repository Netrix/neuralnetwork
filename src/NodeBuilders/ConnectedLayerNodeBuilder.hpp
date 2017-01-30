#pragma once

#include "OperationNodeBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "NodeBuilders/MultipleInputLayerNodeBuilder.hpp"
#include "IConnectedLayerOperationsFactory.hpp"
#include "NodeSpecs.hpp"
#include <string>

struct BuilderStorage;
struct BinaryNodeBuilder;
struct VariableBufferNodeBuilder;
struct ConstBufferNodeBuilder;
struct PassThroughLayerNodeBuilder;

struct ConnectedLayerNodeBuilder : OperationNodeBuilder
{
    ConnectedLayerNodeBuilder(BuilderStorage& builderStorage, ConnectedLayerNodeSpecs specs);

    NotNull<MultipleInputLayerNodeBuilder> setInput(MultipleInputLayerNodeSpecs);
    NotNull<ConnectedLayerNodeBuilder> setInput(ConnectedLayerNodeSpecs);
    NotNull<PassThroughLayerNodeBuilder> setInput(PassThroughLayerNodeSpecs);
    NotNull<ConstBufferNodeBuilder> setInput(ConstBufferNodeSpecs const&);

    ArrayView<OperationNodeBuilder*> getOperations();

    std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps);

private:
    VariableBufferNodeBuilder* allocateVariableNodeBuilder(std::size_t numInputs, std::size_t numOutputs);

private:
    BuilderStorage& m_builderStorage;
    ConnectedLayerNodeSpecs m_specs;

    VariableBufferNodeBuilder* m_variablesNodeBuilder;
    OperationNodeBuilder* m_inputOperationBuilder{};
    NodeBuilder* m_inputBuilder{};
};
