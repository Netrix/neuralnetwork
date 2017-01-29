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
#include "UnaryNodeBuilder.hpp"
#include "MultipleInputNodeBuilder.hpp"
#include <stdexcept>

struct BuilderStorage;

struct BinaryNodeBuilder : OperationNodeBuilder
{
    BinaryNodeBuilder(BuilderStorage& builderStorage, std::string const& operation);    // TODO instead of operation let it pass the factory for the operation, the factory should be able to receive inputs, everything else should be passed through factory constructor

    NotNull<MultipleInputNodeBuilder> setFirstInput(MultipleInputNodeSpecs const& specs);
    NotNull<MultipleInputNodeBuilder> setSecondInput(MultipleInputNodeSpecs const& specs);

    NotNull<UnaryNodeBuilder> setFirstInput(UnaryNodeSpecs);
    NotNull<UnaryNodeBuilder> setSecondInput(UnaryNodeSpecs);

    NotNull<BinaryNodeBuilder> setFirstInput(BinaryNodeSpecs const& specs);
    NotNull<BinaryNodeBuilder> setSecondInput(BinaryNodeSpecs const& specs);

    NotNull<VariableNodeBuilder> setFirstInput(VariableNodeSpecs);
    NotNull<VariableNodeBuilder> setSecondInput(VariableNodeSpecs);

    NotNull<ConstSingleValueNodeBuilder> setFirstInput(ConstNodeSpecs);
    NotNull<ConstSingleValueNodeBuilder> setSecondInput(ConstNodeSpecs);

    void setFirstInput(NotNull<ConstSingleValueNodeBuilder>);
    void setSecondInput(NotNull<ConstSingleValueNodeBuilder>);

    void setFirstInput(NotNull<BinaryNodeBuilder>);
    void setSecondInput(NotNull<BinaryNodeBuilder>);

    void setFirstInput(NotNull<UnaryNodeBuilder>);
    void setSecondInput(NotNull<UnaryNodeBuilder>);

    ArrayView<OperationNodeBuilder*> getOperations() override;

    std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps) override;

private:
    BuilderStorage& m_builderStorage;
    std::string m_operation;

    std::array<OperationNodeBuilder*, 2> m_operationBuilders{};
    std::array<NodeBuilder*, 2> m_inputBuilders{};
};
