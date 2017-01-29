#pragma once

#include "Nodes/ConstSingleValueNode.hpp"
#include "ConstStorageBuilder.hpp"
#include "VariableStorageBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "ConstNodeBuilder.hpp"
#include <memory>

struct ConstSingleValueNodeBuilder : ConstNodeBuilder
{
    std::unique_ptr<ConstNode<BNN_TYPE>> build(ConstStorageBuilder<BNN_TYPE> & constStorage) override
    {
        return std::make_unique<ConstSingleValueNode<BNN_TYPE>>(constStorage.getSingleValueRef());
    }
};
