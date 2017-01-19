#pragma once

#include "NodeBuilder.hpp"
#include "ArrayView.hpp"
#include "NotNull.hpp"
#include "NodeTags.hpp"
#include <array>
#include <cassert>
#include <string>
#include "BinaryOperationNode.hpp"
#include "BuilderToNodeMaps.hpp"

struct BuilderStorage;

struct BinaryNodeBuilder : NodeBuilder
{
    BinaryNodeBuilder(BuilderStorage& builderStorage, std::string const& operation);

    NotNull<BinaryNodeBuilder> setFirstInput(BinaryNodeTag, std::string const& operation);
    NotNull<BinaryNodeBuilder> setSecondInput(BinaryNodeTag, std::string const& operation);

    NotNull<VariableNodeBuilder> setFirstInput(VariableTag);
    NotNull<VariableNodeBuilder> setSecondInput(VariableTag);

    NotNull<ConstNodeBuilder> setFirstInput(ConstTag);
    NotNull<ConstNodeBuilder> setSecondInput(ConstTag);

    void setFirstInput(NotNull<ConstNodeBuilder>);
    void setSecondInput(NotNull<ConstNodeBuilder>);

    ArrayView<BinaryNodeBuilder*> getOperations();

    std::unique_ptr<BinaryOperationNode> build(BuilderToNodeMaps<BNN_TYPE> & builderToNodeMaps);

private:
    BuilderStorage& m_builderStorage;
    std::string m_operation;

    std::array<BinaryNodeBuilder*, 2> m_operationBuilders{};    // Should be changed to OperationNodeBuilder
    std::array<NodeBuilder*, 2> m_inputBuilders{};
};
