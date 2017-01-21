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
#include <stdexcept>

struct InvalidComputationGraph : std::runtime_error
{
    InvalidComputationGraph(std::string const& msg)
        : runtime_error(msg)
    {}
};

struct BuilderStorage;

struct BinaryNodeBuilder : OperationNodeBuilder
{
    BinaryNodeBuilder(BuilderStorage& builderStorage, std::string const& operation);

    NotNull<UnaryNodeBuilder> setFirstInput(UnaryNodeTag, std::string const& operation);
    NotNull<UnaryNodeBuilder> setSecondInput(UnaryNodeTag, std::string const& operation);

    NotNull<BinaryNodeBuilder> setFirstInput(BinaryNodeTag, std::string const& operation);
    NotNull<BinaryNodeBuilder> setSecondInput(BinaryNodeTag, std::string const& operation);

    NotNull<VariableNodeBuilder> setFirstInput(VariableTag);
    NotNull<VariableNodeBuilder> setSecondInput(VariableTag);

    NotNull<ConstNodeBuilder> setFirstInput(ConstTag);
    NotNull<ConstNodeBuilder> setSecondInput(ConstTag);

    void setFirstInput(NotNull<ConstNodeBuilder>);
    void setSecondInput(NotNull<ConstNodeBuilder>);

    ArrayView<OperationNodeBuilder*> getOperations() override;

    std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps) override;

private:
    NotNull<ComputationNode<BNN_TYPE>> getComputationNodeFromMaps(BuilderToNodeMaps<BNN_TYPE> const&, NotNull<NodeBuilder>) const;

    BuilderStorage& m_builderStorage;
    std::string m_operation;

    std::array<OperationNodeBuilder*, 2> m_operationBuilders{};
    std::array<NodeBuilder*, 2> m_inputBuilders{};
};