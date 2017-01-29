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
    BinaryNodeBuilder(BuilderStorage& builderStorage,
                      std::unique_ptr<IBinaryOperationNodesFactory<BNN_TYPE>> factory);

    NotNull<MultipleInputNodeBuilder> setFirstInput(MultipleInputNodeSpecs const& specs);
    NotNull<MultipleInputNodeBuilder> setSecondInput(MultipleInputNodeSpecs const& specs);

    NotNull<UnaryNodeBuilder> setFirstInput(UnaryNodeSpecs);
    NotNull<UnaryNodeBuilder> setSecondInput(UnaryNodeSpecs);

    NotNull<BinaryNodeBuilder> setFirstInput(BinaryNodeSpecs);
    NotNull<BinaryNodeBuilder> setSecondInput(BinaryNodeSpecs);

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
    std::unique_ptr<IBinaryOperationNodesFactory<BNN_TYPE>> m_factory;

    std::array<OperationNodeBuilder*, 2> m_operationBuilders{};
    std::array<NodeBuilder*, 2> m_inputBuilders{};
};
