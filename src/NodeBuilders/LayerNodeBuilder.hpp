#pragma once

#include "OperationNodeBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "NodeBuilders/ConstNodeBuilder.hpp"
#include "NodeBuilders/VariableNodeBuilder.hpp"
#include "NodeBuilders/OperationNodeBuilder.hpp"
#include "NodeBuilders/MultipleInputNodeBuilder.hpp"
#include "ILayerOperationsFactory.hpp"
#include "NodeTags.hpp"
#include <string>
#include <vector>

struct BuilderStorage;
struct BinaryNodeBuilder;

struct LayerNodeBuilder : OperationNodeBuilder
{
    LayerNodeBuilder(BuilderStorage& builderStorage, std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> factory);

    NotNull<MultipleInputNodeBuilder> addInput(MultipleInputTag, std::string const& operation); // TODO can be done by template with traits MultipleInputTag -> MultipleInputNodeBuilder
    NotNull<BinaryNodeBuilder> addInput(BinaryNodeTag, std::string const& operation);
    NotNull<UnaryNodeBuilder> addInput(UnaryNodeTag, std::string const& operation);
    NotNull<VariableNodeBuilder> addInput(VariableTag);
    NotNull<ConstNodeBuilder> addInput(ConstTag);

    void addInput(NotNull<ConstNodeBuilder>);

    ArrayView<OperationNodeBuilder*> getOperations();

    std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps);

private:
    BuilderStorage& m_builderStorage;
    std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> m_factory;

    std::vector<OperationNodeBuilder*> m_inputOperationBuilders;
    std::vector<NodeBuilder*> m_inputBuilders;
};
