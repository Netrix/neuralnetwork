#pragma once

#include "OperationNode.hpp"
#include "BuilderToNodeMaps.hpp"
#include "NodeBuilder.hpp"
#include <memory>

struct OperationNodeBuilder : NodeBuilder
{
    virtual ArrayView<OperationNodeBuilder*> getOperations() = 0;

    virtual std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps) = 0;
};
