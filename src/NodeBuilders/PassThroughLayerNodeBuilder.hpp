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
struct ConnectedLayerNodeBuilder;

struct PassThroughLayerNodeBuilder : OperationNodeBuilder
{
    PassThroughLayerNodeBuilder(BuilderStorage& builderStorage, PassThroughLayerNodeSpecs specs);

    NotNull<MultipleInputLayerNodeBuilder> setInput(MultipleInputLayerNodeSpecs);
    NotNull<ConnectedLayerNodeBuilder> setInput(ConnectedLayerNodeSpecs);
    NotNull<PassThroughLayerNodeBuilder> setInput(PassThroughLayerNodeSpecs);
    NotNull<ConstBufferNodeBuilder> setInput(ConstBufferNodeSpecs const&);

    ArrayView<OperationNodeBuilder*> getOperations();

    std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps);

private:
    BuilderStorage& m_builderStorage;
    PassThroughLayerNodeSpecs m_specs;

    OperationNodeBuilder* m_inputOperationBuilder{};
    NodeBuilder* m_inputBuilder{};
};
