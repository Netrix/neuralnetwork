#pragma once

#include "VariableNode.hpp"
#include "VariableStorageBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "NodeBuilder.hpp"
#include <memory>

struct VariableNodeBuilder : NodeBuilder
{
    std::unique_ptr<VariableNode<BNN_TYPE>> build(VariableStorageBuilder<BNN_TYPE> & variableStorage,
                                                  VariableDeltaStorageBuilder<BNN_TYPE> & variableDeltaStorageBuilder)
    {
        return std::make_unique<VariableNode<BNN_TYPE>>(variableStorage.getSingleValueRef(),
                                                        variableDeltaStorageBuilder.getSingleValueRef());
    }
};
