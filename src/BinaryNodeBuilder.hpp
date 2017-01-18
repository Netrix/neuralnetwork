#pragma once

#include "NodeBuilder.hpp"
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

private:
    BuilderStorage& m_builderStorage;
    std::string m_operation;

    std::array<NodeBuilder*, 2> m_inputBuilders{};
};
