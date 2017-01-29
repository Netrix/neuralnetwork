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
#include "NodeBuilders/ConstNodeBuilder.hpp"
#include "NodeBuilders/VariableNodeBuilder.hpp"
#include "NodeBuilders/OperationNodeBuilder.hpp"
#include "NodeBuilders/MultipleInputNodeBuilder.hpp"

struct BuilderStorage;
struct BinaryNodeBuilder;

struct UnaryNodeBuilder : OperationNodeBuilder
{
    UnaryNodeBuilder(BuilderStorage& builderStorage, std::string const& operation);

    NotNull<MultipleInputNodeBuilder> setInput(MultipleInputNodeSpecs const& specs);
    NotNull<BinaryNodeBuilder> setInput(BinaryNodeSpecs const& specs);
    NotNull<UnaryNodeBuilder> setInput(UnaryNodeSpecs const& specs);
    NotNull<VariableNodeBuilder> setInput(VariableNodeSpecs);
    NotNull<ConstNodeBuilder> setInput(ConstNodeSpecs);

    void setInput(NotNull<ConstNodeBuilder>);

    ArrayView<OperationNodeBuilder*> getOperations();

    std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps);

private:
    BuilderStorage& m_builderStorage;
    std::string m_operation;

    OperationNodeBuilder* m_operationBuilder{};
    NodeBuilder* m_inputBuilder{};
};
