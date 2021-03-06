#pragma once

#include "Nodes/ConstNode.hpp"
#include "ConstStorageBuilder.hpp"
#include "VariableStorageBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "NodeBuilder.hpp"
#include <memory>

struct ConstNodeBuilder : NodeBuilder
{
    virtual std::unique_ptr<ConstNode<BNN_TYPE>> build(ConstStorageBuilder<BNN_TYPE> & constStorage) = 0;
};
