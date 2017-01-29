#pragma once

#include "OperationNodeBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "NodeBuilders/ConstSingleValueNodeBuilder.hpp"
#include "NodeBuilders/VariableNodeBuilder.hpp"
#include "NodeBuilders/OperationNodeBuilder.hpp"
#include "NodeBuilders/MultipleInputNodeBuilder.hpp"
#include "IMultipleInputLayerOperationsFactory.hpp"
#include "NodeTags.hpp"
#include <string>
#include <vector>

struct BuilderStorage;
struct BinaryNodeBuilder;

struct MultipleInputLayerNodeBuilder : OperationNodeBuilder
{
    MultipleInputLayerNodeBuilder(BuilderStorage& builderStorage, std::unique_ptr<IMultipleInputLayerOperationsFactory<BNN_TYPE>> factory);

    NotNull<MultipleInputNodeBuilder> addInput(MultipleInputNodeSpecs const& specs);
    NotNull<BinaryNodeBuilder> addInput(BinaryNodeSpecs);
    NotNull<UnaryNodeBuilder> addInput(UnaryNodeSpecs);
    NotNull<VariableNodeBuilder> addInput(VariableNodeSpecs);
    NotNull<ConstSingleValueNodeBuilder> addInput(ConstNodeSpecs);

    void addInput(NotNull<ConstSingleValueNodeBuilder>);

    ArrayView<OperationNodeBuilder*> getOperations();

    std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps);

private:
    BuilderStorage& m_builderStorage;
    std::unique_ptr<IMultipleInputLayerOperationsFactory<BNN_TYPE>> m_factory;

    std::vector<OperationNodeBuilder*> m_inputOperationBuilders;
    std::vector<NodeBuilder*> m_inputBuilders;
};
