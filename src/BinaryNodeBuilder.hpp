#pragma once

#include "NodeBuilder.hpp"
#include "ArrayView.hpp"
#include "NotNull.hpp"
#include "NodeTags.hpp"
#include <array>
#include <cassert>
#include <string>

struct BuilderStorage;

struct BinaryNodeBuilder : NodeBuilder
{
    BinaryNodeBuilder(BuilderStorage& builderStorage, std::string const& operation);

    NotNull<BinaryNodeBuilder> setFirstInput(BinaryNode, std::string const& operation);
    NotNull<BinaryNodeBuilder> setSecondInput(BinaryNode, std::string const& operation);

    NotNull<VariableNodeBuilder> setFirstInput(Variable);
    NotNull<VariableNodeBuilder> setSecondInput(Variable);

    NotNull<ConstNodeBuilder> setFirstInput(Const);
    NotNull<ConstNodeBuilder> setSecondInput(Const);

    void setFirstInput(NotNull<ConstNodeBuilder>);
    void setSecondInput(NotNull<ConstNodeBuilder>);

    ArrayView<BinaryNodeBuilder*> getOperations();

private:
    BuilderStorage& m_builderStorage;
    std::string m_operation;

    std::array<BinaryNodeBuilder*, 2> m_operationBuilders{};    // Should be changed to OperationNodeBuilder
    std::array<NodeBuilder*, 2> m_inputBuilders{};
};
