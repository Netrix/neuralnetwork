#pragma once

#include "NotNull.hpp"
#include "NodeBuilders/NodeBuilder.hpp"
#include "NodeBuilders/BinaryNodeBuilder.hpp"
#include "NodeBuilders/UnaryNodeBuilder.hpp"
#include "NodeBuilders/ConstNodeBuilder.hpp"
#include "NodeBuilders/MultipleInputNodeBuilder.hpp"
#include "NodeBuilders/MultipleInputLayerNodeBuilder.hpp"
#include "NodeBuilders/LayerNodeBuilder.hpp"
#include <string>
#include <vector>
#include <memory>


struct BuilderStorage
{
    NotNull<MultipleInputNodeBuilder> createMultipleInputNodeBuilder(std::string const& operation);
    NotNull<UnaryNodeBuilder> createUnaryNodeBuilder(std::string const& operation);
    NotNull<BinaryNodeBuilder> createBinaryNodeBuilder(std::string const& operation);
    NotNull<MultipleInputLayerNodeBuilder> createMultipleInputLayerNodeBuilder(std::unique_ptr<IMultipleInputLayerOperationsFactory<BNN_TYPE>> factory);
    NotNull<LayerNodeBuilder> createLayerNodeBuilder(std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> factory);
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
    std::vector<std::unique_ptr<OperationNodeBuilder>> operations; // should have generic operations later
};
