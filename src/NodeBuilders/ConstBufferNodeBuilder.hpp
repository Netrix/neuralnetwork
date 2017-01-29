#pragma once

#include "Nodes/ConstBufferNode.hpp"
#include "ConstStorageBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "ConstNodeBuilder.hpp"
#include <memory>


struct ConstBufferNodeBuilder : ConstNodeBuilder
{
    ConstBufferNodeBuilder(std::size_t numConsts)
        : m_numConsts(numConsts)
    {}

    std::unique_ptr<ConstNode<BNN_TYPE>> build(ConstStorageBuilder<BNN_TYPE> & constStorage) override
    {
        return std::make_unique<ConstBufferNode<BNN_TYPE>>(constStorage.getValues(m_numConsts));
    }

private:
    std::size_t m_numConsts;
};
