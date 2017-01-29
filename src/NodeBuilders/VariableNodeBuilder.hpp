#pragma once

#include "VariableStorageBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "NodeBuilder.hpp"
#include <memory>

struct VariableNodeBuilder : NodeBuilder
{
    virtual std::unique_ptr<VariableNode<BNN_TYPE>> build(VariableStorageBuilder<BNN_TYPE> & variableStorage,
                                                          VariableDeltaStorageBuilder<BNN_TYPE> & variableDeltaStorageBuilder) = 0;
};
