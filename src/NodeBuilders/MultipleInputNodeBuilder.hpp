#pragma once

#include "NodeBuilder.hpp"
#include "ArrayView.hpp"
#include "NotNull.hpp"
#include "NodeTags.hpp"
#include <array>
#include <string>
#include "OperationNodeBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include <stdexcept>

struct BuilderStorage;
struct UnaryNodeBuilder;
struct BinaryNodeBuilder;
struct VariableNodeBuilder;
struct ConstNodeBuilder;

struct MultipleInputNodeBuilder : OperationNodeBuilder
{
    MultipleInputNodeBuilder(BuilderStorage& builderStorage, std::string const& operation);

    NotNull<UnaryNodeBuilder> addInput(UnaryNodeSpecs const& specs);
    NotNull<BinaryNodeBuilder> addInput(BinaryNodeSpecs const& specs);
    NotNull<VariableNodeBuilder> addInput(VariableNodeSpecs);
    NotNull<ConstNodeBuilder> addInput(ConstNodeSpecs);

    void addInput(NotNull<ConstNodeBuilder>);

    ArrayView<OperationNodeBuilder*> getOperations() override;

    std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps) override;

private:
    BuilderStorage& m_builderStorage;
    std::string m_operation;

    std::vector<OperationNodeBuilder*> m_operationBuilders;
    std::vector<NodeBuilder*> m_inputBuilders;
};
