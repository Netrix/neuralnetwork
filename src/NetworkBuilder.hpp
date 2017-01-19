#pragma once

#include "NotNull.hpp"
#include "NodeTags.hpp"
#include "BuilderStorage.hpp"
#include "ConstNode.hpp"
#include "VariableNode.hpp"
#include "ConstStorageBuilder.hpp"
#include "VariableStorageBuilder.hpp"
#include "BackPropagationNetwork.hpp"
#include <map>


struct BinaryNodeBuilder;



struct ForwardNetwork{};



struct NetworkBuilder
{
    NotNull<BinaryNodeBuilder> setRootNode(BinaryNodeTag, std::string const& operation);

    std::unique_ptr<BackPropagationNetwork> buildBackPropagationNetwork() const;   // should verify entire tree and return ready to work tree

    std::unique_ptr<ForwardNetwork> buildForwardNetwork();

private:
    std::vector<BinaryNodeBuilder*> getOperationNodesInTopologicalOrder() const;
    ConstBuilderToNodeMap<BNN_TYPE> getConstNodeMap(ConstStorageBuilder<BNN_TYPE> & constStorage) const;
    VariableBuilderToNodeMap<BNN_TYPE> getVariableNodeMap(VariableStorageBuilder<BNN_TYPE> & variableStorageBuilder) const;

    BuilderStorage m_storage;
    BinaryNodeBuilder* m_root; // should be generic operation later // should be able to get topology from here to get forward list to do operations
};
