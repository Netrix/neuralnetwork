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

    NotNull<MultipleInputNodeBuilder> setFirstInput(MultipleInputTag, std::string const& operation);
    NotNull<MultipleInputNodeBuilder> setSecondInput(MultipleInputTag, std::string const& operation);

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
