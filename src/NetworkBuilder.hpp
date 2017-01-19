#pragma once

#include "NotNull.hpp"
#include "NodeTags.hpp"
#include "BuilderStorage.hpp"
#include "ConstNode.hpp"
#include "ConstStorageBuilder.hpp"
#include <map>

struct BinaryNodeBuilder;

struct BackPropagatioNode
{

};

struct BackPropagationNetwork
{
private:
    std::vector<BackPropagatioNode*> m_nodes;
};

struct ForwardNetwork{};

struct NetworkBuilder
{
    NotNull<BinaryNodeBuilder> setRootNode(BinaryNode, std::string const& operation);

    std::unique_ptr<BackPropagationNetwork> buildBackPropagationNetwork() const;   // should verify entire tree and return ready to work tree

    std::unique_ptr<ForwardNetwork> buildForwardNetwork();

private:
    std::vector<BinaryNodeBuilder*> getOperationNodesInTopologicalOrder() const;
    std::map<ConstNodeBuilder*, std::unique_ptr<ConstNode<BNN_TYPE>>> getConstNodeMap(ConstStorageBuilder<BNN_TYPE> & constStorage) const;

    BuilderStorage m_storage;
    BinaryNodeBuilder* m_root; // should be generic operation later // should be able to get topology from here to get forward list to do operations
};
