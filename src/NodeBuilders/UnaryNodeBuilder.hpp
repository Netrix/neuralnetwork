#pragma once

#include "NodeBuilder.hpp"
#include "ArrayView.hpp"
#include "NotNull.hpp"
#include "NodeTags.hpp"
#include <array>
#include <cassert>
#include <string>
#include "OperationNodeBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "NodeBuilders/ConstSingleValueNodeBuilder.hpp"
#include "NodeBuilders/VariableNodeBuilder.hpp"
#include "NodeBuilders/OperationNodeBuilder.hpp"
#include "NodeBuilders/MultipleInputNodeBuilder.hpp"
#include "UnaryOperationNodesFactories/IUnaryOperationNodesFactory.hpp"

struct BuilderStorage;
struct BinaryNodeBuilder;

struct UnaryNodeBuilder : OperationNodeBuilder
{
    UnaryNodeBuilder(BuilderStorage& builderStorage, std::unique_ptr<IUnaryOperationNodesFactory<BNN_TYPE>> factory);

    NotNull<MultipleInputNodeBuilder> setInput(MultipleInputNodeSpecs const& specs);
    NotNull<BinaryNodeBuilder> setInput(BinaryNodeSpecs const& specs);
    NotNull<UnaryNodeBuilder> setInput(UnaryNodeSpecs);
    NotNull<VariableNodeBuilder> setInput(VariableNodeSpecs);
    NotNull<ConstSingleValueNodeBuilder> setInput(ConstNodeSpecs);

    void setInput(NotNull<ConstSingleValueNodeBuilder>);

    ArrayView<OperationNodeBuilder*> getOperations();

    std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps);

private:
    BuilderStorage& m_builderStorage;
    std::unique_ptr<IUnaryOperationNodesFactory<BNN_TYPE>> m_factory;

    OperationNodeBuilder* m_operationBuilder{};
    NodeBuilder* m_inputBuilder{};
};
