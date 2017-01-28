#pragma once

#include "Nodes/VariableBufferNode.hpp"
#include "VariableStorageBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "VariableNodeBuilder.hpp"
#include <memory>


struct VariableBufferNodeBuilder : VariableNodeBuilder
{
    VariableBufferNodeBuilder(std::size_t numVariables)
        : m_numVariables(numVariables)
    {}

    std::unique_ptr<VariableBufferNode<BNN_TYPE>> build(VariableStorageBuilder<BNN_TYPE> & variableStorage,
                                                  VariableDeltaStorageBuilder<BNN_TYPE> & variableDeltaStorageBuilder)
    {
        return std::make_unique<VariableBufferNode<BNN_TYPE>>(variableStorage.getValues(m_numVariables),
                                                              variableDeltaStorageBuilder.getValues(m_numVariables));
    }

private:
    std::size_t m_numVariables;
};
