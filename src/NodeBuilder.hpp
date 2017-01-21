#pragma once

#include "ConstNode.hpp"
#include "VariableNode.hpp"
#include "ConstStorageBuilder.hpp"
#include "VariableStorageBuilder.hpp"
#include "OperationNode.hpp"
#include "BuilderToNodeMaps.hpp"
#include <memory>

using BNN_TYPE = float;

struct NodeBuilder
{
    virtual ~NodeBuilder() = default;
};

struct ConstNodeBuilder : NodeBuilder
{
    std::unique_ptr<ConstNode<BNN_TYPE>> build(ConstStorageBuilder<BNN_TYPE> & constStorage)
    {
        return std::make_unique<ConstNode<BNN_TYPE>>(constStorage.getSingleValueRef());
    }
};

struct VariableNodeBuilder : NodeBuilder
{
    std::unique_ptr<VariableNode<BNN_TYPE>> build(VariableStorageBuilder<BNN_TYPE> & variableStorage,
                                                  VariableDeltaStorageBuilder<BNN_TYPE> & variableDeltaStorageBuilder)
    {
        return std::make_unique<VariableNode<BNN_TYPE>>(variableStorage.getSingleValueRef(),
                                                        variableDeltaStorageBuilder.getSingleValueRef());
    }
};


struct OperationNodeBuilder : NodeBuilder
{
    virtual ArrayView<OperationNodeBuilder*> getOperations() = 0;

    virtual std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps) = 0;
};
