#pragma once

#include "NotNull.hpp"
#include "NodeBuilder.hpp"
#include "BinaryNodeBuilder.hpp"
#include <string>
#include <vector>
#include <memory>


struct BuilderStorage
{
    NotNull<BinaryNodeBuilder> createBinaryNodeBuilder(std::string const& operation);
    NotNull<VariableNodeBuilder> createVariableNodeBuilder();
    NotNull<ConstNodeBuilder> createConstNodeBuilder();

    std::size_t getNumConsts() const
    {
        return consts.size();
    }

    std::size_t getNumVariables() const
    {
        return variables.size();
    }

    auto const& getConstBuilders() const
    {
        return consts;
    }

    auto const& getVariableBuilders() const
    {
        return variables;
    }

private:
    std::vector<std::unique_ptr<ConstNodeBuilder>> consts;
    std::vector<std::unique_ptr<VariableNodeBuilder>> variables;
    std::vector<std::unique_ptr<BinaryNodeBuilder>> operations; // should have generic operations later
};