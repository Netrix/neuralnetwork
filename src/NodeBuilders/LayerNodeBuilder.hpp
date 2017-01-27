#pragma once

#include "OperationNodeBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "NodeBuilders/MultipleInputLayerNodeBuilder.hpp"
#include "ILayerOperationsFactory.hpp"
#include "NodeTags.hpp"
#include <string>
#include <vector>

struct BuilderStorage;
struct BinaryNodeBuilder;

struct LayerNodeBuilder : OperationNodeBuilder
{
    LayerNodeBuilder(BuilderStorage& builderStorage, std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> factory);

    NotNull<MultipleInputLayerNodeBuilder> setInput(MultipleInputLayerNodeTag, std::string const& operation); // TODO can be done by template with traits MultipleInputTag -> MultipleInputNodeBuilder

    ArrayView<OperationNodeBuilder*> getOperations();

    std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps);

private:
    BuilderStorage& m_builderStorage;
    std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> m_factory;

    OperationNodeBuilder* m_inputOperationBuilder;
    NodeBuilder* m_inputBuilder;
};
