#pragma once

#include "ConstNode.hpp"
#include "ConstStorageBuilder.hpp"
#include <memory>

using BNN_TYPE = float;

struct NodeBuilder
{
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
};
