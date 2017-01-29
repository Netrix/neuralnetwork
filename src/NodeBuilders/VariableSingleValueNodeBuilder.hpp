#pragma once

#include "Nodes/VariableSingleValueNode.hpp"
#include "VariableStorageBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "VariableNodeBuilder.hpp"
#include <memory>

struct VariableSingleValueNodeBuilder : VariableNodeBuilder
{
    std::unique_ptr<VariableNode<BNN_TYPE>> build(VariableStorageBuilder<BNN_TYPE> & variableStorage,
                                                  VariableDeltaStorageBuilder<BNN_TYPE> & variableDeltaStorageBuilder) override
    {
        return std::make_unique<VariableSingleValueNode<BNN_TYPE>>(variableStorage.getSingleValueRef(),
                                                                   variableDeltaStorageBuilder.getSingleValueRef());
    }
};
